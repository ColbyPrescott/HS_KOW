// Container object to hold variables related to mouse input
const mouse = {
    // Previous position of the mouse in field coordinate space before the most recent movement event trigger
    prevPosition: new Vec2(),
    // Current position of the mouse in field coordinate space
    position: new Vec2(),
    // Distance the mouse traveled between the previous and most recent event trigger
    velocity: new Vec2(),

    // The Vec2 point that is being dragged around
    heldPathSectionPoint: undefined,
    // The PathSection that has the point being dragged around
    heldPathSection: undefined,
    // The PathSection that comes directly before heldPathSection in the path
    heldPrevPathSection: undefined,
    // The PathSection that comes directly after heldPathSection in the path
    heldNextPathSection: undefined,

    // The last PathSection that was clicked on
    selectedPathSection: undefined,

    // Function that gets called whenever the mouse moves
    OnMouseMove(event) {
        // Copy the now outdated position to prevPosition
        this.prevPosition = new Vec2(this.position);
        // Update mouse position, converting screen coordinates to the canvas's field coordinates
        this.position = new Vec2(
            Map(event.clientX, 0, canvas.width, 0, fieldSize.x),
            Map(event.clientY, 0, canvas.height, fieldSize.y, 0)
        );
        // Calculate the movement from prevPosition to position
        this.velocity = new Vec2(this.position).Translate(new Vec2(this.prevPosition).Scale(-1));


        // Don't try to move anything if nothing is held
        if(this.heldPathSection == undefined) return;

        // Move all points connected to p0
        if(this.heldPathSectionPoint == this.heldPathSection.p0) {
            this.heldPathSection.p0.Translate(this.velocity); // Move the anchor point
            this.heldPathSection.p1.Translate(this.velocity); // and the control point
            if(this.heldPrevPathSection == undefined) return;
            this.heldPrevPathSection.p3.Translate(this.velocity); // Move the anchor point on the previous section
            this.heldPrevPathSection.p2.Translate(this.velocity); // and the control point on the previous section

        // Move all points connected to p1
        } else if(this.heldPathSectionPoint == this.heldPathSection.p1) {
            this.heldPathSection.p1.Translate(this.velocity); // Move the control point
            if(this.heldPrevPathSection == undefined) return;
            this.heldPrevPathSection.p2 = new Vec2(this.heldPathSection.p1); // Mirror the control point on the previous section
            this.heldPrevPathSection.p2.Translate(new Vec2(this.heldPathSection.p0).Scale(-1));
            this.heldPrevPathSection.p2.Rotate(Math.PI);
            this.heldPrevPathSection.p2.Translate(this.heldPathSection.p0);

        // Move all points connected to p2
        } else if(this.heldPathSectionPoint == this.heldPathSection.p2) {
            this.heldPathSection.p2.Translate(this.velocity); // Move the control point
            if(this.heldNextPathSection == undefined) return;
            this.heldNextPathSection.p1 = new Vec2(this.heldPathSection.p2); // Mirror the control point on the next section
            this.heldNextPathSection.p1.Translate(new Vec2(this.heldPathSection.p3).Scale(-1));
            this.heldNextPathSection.p1.Rotate(Math.PI);
            this.heldNextPathSection.p1.Translate(this.heldPathSection.p3);

        // Move all points connected to p3
        } else if(this.heldPathSectionPoint == this.heldPathSection.p3) {
            this.heldPathSection.p3.Translate(this.velocity); // Move the anchor point
            this.heldPathSection.p2.Translate(this.velocity); // and the control point
            if(this.heldNextPathSection == undefined) return;
            this.heldNextPathSection.p0.Translate(this.velocity); // Move the anchor point on the next section
            this.heldNextPathSection.p1.Translate(this.velocity); // and the control point on the next section
        }
    },

    // Function that gets called whenever the left mouse button is pressed down
    OnMouseDown(event) {
        // If the user did something weird like a right click, simply ignore it
        if(this.heldPathSection != undefined) return;

        // Loop through every PathSection and attempt to grab something
        for(let i = 0; i < path.pathSections.length; i++) {
            // Try to grab one of the four points making up the cubic bezier curve
            // Ordered 1, 2, 0, 3 so the smaller control points can't be covered by the anchor points
            if      (Math.pow(this.position.x - path.pathSections[i].p1.x, 2) + Math.pow(this.position.y - path.pathSections[i].p1.y, 2) <= Math.pow(theme.controlPointRadius,  2)) this.heldPathSectionPoint = path.pathSections[i].p1;
            else if (Math.pow(this.position.x - path.pathSections[i].p2.x, 2) + Math.pow(this.position.y - path.pathSections[i].p2.y, 2) <= Math.pow(theme.controlPointRadius, 2)) this.heldPathSectionPoint = path.pathSections[i].p2;
            else if (Math.pow(this.position.x - path.pathSections[i].p0.x, 2) + Math.pow(this.position.y - path.pathSections[i].p0.y, 2) <= Math.pow(theme.anchorPointRadius, 2)) this.heldPathSectionPoint = path.pathSections[i].p0;
            else if (Math.pow(this.position.x - path.pathSections[i].p3.x, 2) + Math.pow(this.position.y - path.pathSections[i].p3.y, 2) <= Math.pow(theme.anchorPointRadius,  2)) this.heldPathSectionPoint = path.pathSections[i].p3;
            
            // If nothing was grabbed, continue searching through the PathSections
            if(this.heldPathSectionPoint == undefined) continue;

            // Set up references to different parts of the path that need to be controlled in OnMouseMove
            this.heldPathSection = path.pathSections[i];
            if(i > 0) this.heldPrevPathSection = path.pathSections[i - 1];
            if(i < path.pathSections.length - 1) this.heldNextPathSection = path.pathSections[i + 1];

            // Set reference to the selected PathSection
            this.selectedPathSection = path.pathSections[i];

            // Something to grab was found, no need to continue searching
            break;
        }

        // If the mouse clicked air, deselect the selectedPathSection
        if(this.heldPathSection == undefined) this.selectedPathSection = undefined;
    },

    // Function that gets called whenever the left mouse button is released
    OnMouseUp(event) {
        // Release whatever is held, break the references so they stop getting updated
        this.heldPathSectionPoint = undefined;
        this.heldPathSection = undefined;
        this.heldPrevPathSection = undefined;
        this.heldNextPathSection = undefined;
    }

};

// Set up the event listeners
document.body.addEventListener("mousemove", (event) => {mouse.OnMouseMove(event);});
document.body.addEventListener("mousedown", (event) => {mouse.OnMouseDown(event);});
document.body.addEventListener("mouseup", (event) => {mouse.OnMouseUp(event);});

document.body.addEventListener("keydown", (event) => {if(event.key == " ") path.AddPathSection();});