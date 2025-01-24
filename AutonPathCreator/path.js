// Container object for everything related to the path being edited
const path = {
    // Array of all the different sections that make up the path
    pathSections: [],

    AddFirstPathSection() {
        let pathSection = new PathSection();
        this.pathSections.push(pathSection);
        for(let vertex of [pathSection.p0, pathSection.p1, pathSection.p2, pathSection.p3]) vertex.Translate(new Vec2(50, 50));
    },

    PrependPathSection() {
        // Create a single disconnected PathSection for the first PathSection
        if(this.pathSections.length == 0) {
            this.AddFirstPathSection();
            return;
        }

        // Get the PathSection that this new one is being attatched to
        let nextPathSection = this.pathSections[0];

        // Create new PathSection
        let newPathSection = new PathSection();
        this.pathSections.splice(0, 0, newPathSection);
        // Transform the points to be at the end of prevPathSection
        for(let vertex of [newPathSection.p0, newPathSection.p1, newPathSection.p2, newPathSection.p3]) {
            vertex.Translate(new Vec2(newPathSection.p3).Scale(-1));
            vertex.Rotate(Math.atan2(nextPathSection.p1.y - nextPathSection.p0.y, nextPathSection.p1.x - nextPathSection.p0.x));
            vertex.Translate(nextPathSection.p0);
        }
    },

    AppendPathSection() {
        // Create a single disconnected PathSection for the first PathSection
        if(this.pathSections.length == 0) {
            this.AddFirstPathSection();
            return;
        }

        // Get the PathSection that this new one is being attatched to
        let prevPathSection = this.pathSections[this.pathSections.length - 1];

        // Create new PathSection
        let newPathSection = new PathSection();
        this.pathSections.push(newPathSection);
        // Transform the points to be at the end of prevPathSection
        for(let vertex of [newPathSection.p0, newPathSection.p1, newPathSection.p2, newPathSection.p3]) {
            vertex.Rotate(Math.atan2(prevPathSection.p2.y - prevPathSection.p3.y, prevPathSection.p2.x - prevPathSection.p3.x) + Math.PI);
            vertex.Translate(prevPathSection.p3);
        }
    },

    SplitPathSection(targetPathSection) {
        // Insert a new PathSection into the path
        let index = this.pathSections.indexOf(targetPathSection);
        let newPathSection = new PathSection();
        this.pathSections.splice(index + 1, 0, newPathSection);

        // Get key points
        let start = targetPathSection.GetPoint(0);
        let firstControl = targetPathSection.p1;
        let middle = targetPathSection.GetPoint(0.5);
        let lastControl = targetPathSection.p2;
        let end = targetPathSection.GetPoint(1);

        // Set the position of each point in the two PathSections
        targetPathSection.p0 = new Vec2(start);
        targetPathSection.p1 = new Vec2(firstControl);
        targetPathSection.p2 = new Vec2(middle);
        targetPathSection.p3 = new Vec2(middle);
        newPathSection.p0 = new Vec2(middle);
        newPathSection.p1 = new Vec2(middle);
        newPathSection.p2 = new Vec2(lastControl);
        newPathSection.p3 = new Vec2(end);
    },

    RemovePathSectionPoint(targetPathSection, targetPathSectionPoint) {
        // Don't remove anything if a control point is selected
        if(targetPathSectionPoint == targetPathSection.p1 || targetPathSectionPoint == targetPathSection.p2) return;

        // Simply delete a PathSection if the path's entire beginning or end is selected
        if(targetPathSectionPoint == this.pathSections[0].p0) {
            this.pathSections.shift();
            return;
        }
        if(targetPathSectionPoint == this.pathSections[this.pathSections.length - 1].p3) {
            this.pathSections.pop();
            return;
        }

        // Organize the two PathSections that contain the targetPathSectionPoint into the earlier and later PathSection
        let targetIndex = this.pathSections.indexOf(targetPathSection);
        let prevIndex;
        let nextIndex;
        let prevPathSection;
        let nextPathSection;
        if(targetPathSectionPoint == targetPathSection.p0) {
            prevIndex = targetIndex - 1;
            nextIndex = targetIndex;
            prevPathSection = this.pathSections[targetIndex - 1];
            nextPathSection = targetPathSection;
        } else if(targetPathSectionPoint == targetPathSection.p3) {
            prevIndex = targetIndex;
            nextIndex = targetIndex + 1;
            prevPathSection = targetPathSection;
            nextPathSection = this.pathSections[targetIndex + 1];
        }

        // Remove a PathSection from the path
        path.pathSections.splice(nextIndex, 1);

        // Get key points
        let start = prevPathSection.p0;
        let firstControl = prevPathSection.p1;
        let lastControl = nextPathSection.p2;
        let end = nextPathSection.p3;

        // Glue the end of the prevPathSection to the end of the nextPathSection
        prevPathSection.p0 = new Vec2(start);
        prevPathSection.p1 = new Vec2(firstControl);
        prevPathSection.p2 = new Vec2(lastControl);
        prevPathSection.p3 = new Vec2(end);
    },

    Draw() {
        // Draw each part of the PathSections in layers so all elements are ordered by importance rather than their order in the array
        for(let pathSection of this.pathSections) pathSection.DrawCurve();
        for(let pathSection of this.pathSections) pathSection.DrawControlPoints();
        for(let pathSection of this.pathSections) pathSection.DrawAnchorPoints();
    }

};