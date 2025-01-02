// Container object for everything related to the path being edited
const path = {
    // Array of all the different sections that make up the path
    pathSections: [],

    AddPathSection() {
        // Create a single disconnected PathSection for the first PathSection
        if(this.pathSections.length == 0) {
            let pathSection = new PathSection();
            this.pathSections.push(pathSection);
            for(let vertex of [pathSection.p0, pathSection.p1, pathSection.p2, pathSection.p3]) vertex.Translate(new Vec2(50, 50));
            return;
        }

        // Get the PathSection that this new one is being attatched to
        let prevPathSection = this.pathSections[this.pathSections.length - 1];

        let pathSection = new PathSection();
        this.pathSections.push(pathSection);
        for(let vertex of [pathSection.p0, pathSection.p1, pathSection.p2, pathSection.p3]) {
            vertex.Rotate(Math.atan2(prevPathSection.p2.y - prevPathSection.p3.y, prevPathSection.p2.x - prevPathSection.p3.x) + Math.PI);
            vertex.Translate(prevPathSection.p3);
        }

        // // Weld the end of the last PathSection and the start of the new PathSection
        pathSection.p0 = prevPathSection.p3;
    },

    Draw() {
        for(let pathSection of this.pathSections) pathSection.DrawCurve();
        for(let pathSection of this.pathSections) pathSection.DrawControlPoints();
        for(let pathSection of this.pathSections) pathSection.DrawAnchorPoints();
    }

};