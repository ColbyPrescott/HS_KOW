// Container object to hold variables related to mouse input
const input = {
    mouse: {
        // Previous position of the mouse in field coordinate space before the most recent movement event trigger
        prevPosition: new Vec2(),
        // Current position of the mouse in field coordinate space
        position: new Vec2(),
        // Distance the mouse traveled between the previous and most recent event trigger
        velocity: new Vec2()
    },

    // Reference to the Vec2 point that is currently selected
    selectedPathSectionPoint: undefined,
    // Reference to the PathSection that has the selectedPathSectionPoint
    selectedPathSection: undefined,
    // Reference to the PathSection that comes directly before selectedPathSection in the path
    selectedPrevPathSection: undefined,
    // Reference to the PathSection that comes directly after selectedPathSection in the path
    selectedNextPathSection: undefined,
    // Whether or not the selectedPathSectionPoint is actively being moved around
    draggingSelectedPathSectionPoint: false,

    DeselectPathSection() {
        this.selectedPathSectionPoint = undefined;
        this.selectedPathSection = undefined;
        this.selectedPrevPathSection = undefined;
        this.selectedNextPathSection = undefined;
        this.draggingSelectedPathSectionPoint = false;
    },

    MoveSelectedP0(newPosition) {
        // Don't move if nothing is selected
        if(this.selectedPathSection == undefined) return;
        
        // Calculate how much points need to be translated by
        let offset = new Vec2(newPosition).Translate(new Vec2(this.selectedPathSection.p0).Scale(-1));

        // Move the anchor and control point on the selected section
        this.selectedPathSection.p0.Translate(offset);
        this.selectedPathSection.p1.Translate(offset);
        // Move the anchor and control point on the previous section
        if(this.selectedPrevPathSection == undefined) return;
        this.selectedPrevPathSection.p3.Translate(offset);
        this.selectedPrevPathSection.p2.Translate(offset);
    },

    MoveSelectedP1(newPosition) {
        // Don't move if nothing is selected
        if(this.selectedPathSection == undefined) return;
        
        // Calculate how much points need to be translated by
        let offset = new Vec2(newPosition).Translate(new Vec2(this.selectedPathSection.p1).Scale(-1));

        // Move the control point
        this.selectedPathSection.p1.Translate(offset); 
        // Mirror the control point on the previous section
        if(this.selectedPrevPathSection == undefined) return;
        this.selectedPrevPathSection.p2 = new Vec2(this.selectedPathSection.p1); 
        this.selectedPrevPathSection.p2.Translate(new Vec2(this.selectedPathSection.p0).Scale(-1));
        this.selectedPrevPathSection.p2.Rotate(Math.PI);
        this.selectedPrevPathSection.p2.Translate(this.selectedPathSection.p0);
    },

    MoveSelectedP2(newPosition) {
        // Don't move if nothing is selected
        if(this.selectedPathSection == undefined) return;
        
        // Calculate how much points need to be translated by
        let offset = new Vec2(newPosition).Translate(new Vec2(this.selectedPathSection.p2).Scale(-1));

        // Move the control point
        this.selectedPathSection.p2.Translate(offset); 
        // Mirror the control point on the next section
        if(this.selectedNextPathSection == undefined) return;
        this.selectedNextPathSection.p1 = new Vec2(this.selectedPathSection.p2); 
        this.selectedNextPathSection.p1.Translate(new Vec2(this.selectedPathSection.p3).Scale(-1));
        this.selectedNextPathSection.p1.Rotate(Math.PI);
        this.selectedNextPathSection.p1.Translate(this.selectedPathSection.p3);
    },

    MoveSelectedP3(newPosition) {
        // Don't move if nothing is selected
        if(this.selectedPathSection == undefined) return;
        
        // Calculate how much points need to be translated by
        let offset = new Vec2(newPosition).Translate(new Vec2(this.selectedPathSection.p3).Scale(-1));

        // Move the anchor and control point on the selected section
        this.selectedPathSection.p3.Translate(offset);
        this.selectedPathSection.p2.Translate(offset);
         // Move the anchor and control point on the previous section
        if(this.selectedNextPathSection == undefined) return;
        this.selectedNextPathSection.p0.Translate(offset);
        this.selectedNextPathSection.p1.Translate(offset);
    },

    // Function that gets called whenever the mouse moves
    OnMouseMove(event) {
        // Copy the now outdated position to prevPosition
        this.mouse.prevPosition = new Vec2(this.mouse.position);
        // Update mouse position, converting screen coordinates to the canvas's field coordinates
        this.mouse.position = new Vec2(
            Map(event.clientX, 0, canvas.width / theme.canvasQualityMultiplier, 0, fieldSize.x),
            Map(event.clientY, 0, canvas.height / theme.canvasQualityMultiplier, fieldSize.y, 0)
        );
        // Calculate the movement from prevPosition to position
        this.mouse.velocity = new Vec2(this.mouse.position).Translate(new Vec2(this.mouse.prevPosition).Scale(-1));


        // Don't try to move anything if nothing is held
        if(!this.draggingSelectedPathSectionPoint) return;

        // Add the mouse's velocity to the selectedPathSectionPoint so that the point's center doesn't teleport to the mouse
        let newPointPosition = new Vec2(this.selectedPathSectionPoint).Translate(this.mouse.velocity);

        // Update the position of whichever point is grabbed. Different points move and rotate other points with them
        if(this.selectedPathSectionPoint == this.selectedPathSection.p0) this.MoveSelectedP0(newPointPosition);
        else if(this.selectedPathSectionPoint == this.selectedPathSection.p1) this.MoveSelectedP1(newPointPosition);
        else if(this.selectedPathSectionPoint == this.selectedPathSection.p2) this.MoveSelectedP2(newPointPosition);
        else if(this.selectedPathSectionPoint == this.selectedPathSection.p3) this.MoveSelectedP3(newPointPosition);

        UpdateUI();
    },

    // Function that gets called whenever the left mouse button is pressed down
    OnMouseDown(event) {
        // If the user did something weird like a right click and a mouseDown event is being fired despite something already being dragged, simply ignore it
        if(this.draggingSelectedPathSectionPoint) return;

        // Deselect the object that is currently held
        this.DeselectPathSection();

        // Loop through every PathSection and attempt to grab something
        for(let i = 0; i < path.pathSections.length; i++) {
            // Try to grab one of the four points making up the cubic bezier curve
            // Ordered 1, 2, 0, 3 so the smaller control points can't be covered by the anchor points
            if      (Math.pow(this.mouse.position.x - path.pathSections[i].p1.x, 2) + Math.pow(this.mouse.position.y - path.pathSections[i].p1.y, 2) <= Math.pow(theme.controlPointRadius,  2)) this.selectedPathSectionPoint = path.pathSections[i].p1;
            else if (Math.pow(this.mouse.position.x - path.pathSections[i].p2.x, 2) + Math.pow(this.mouse.position.y - path.pathSections[i].p2.y, 2) <= Math.pow(theme.controlPointRadius, 2)) this.selectedPathSectionPoint = path.pathSections[i].p2;
            else if (Math.pow(this.mouse.position.x - path.pathSections[i].p0.x, 2) + Math.pow(this.mouse.position.y - path.pathSections[i].p0.y, 2) <= Math.pow(theme.anchorPointRadius, 2)) this.selectedPathSectionPoint = path.pathSections[i].p0;
            else if (Math.pow(this.mouse.position.x - path.pathSections[i].p3.x, 2) + Math.pow(this.mouse.position.y - path.pathSections[i].p3.y, 2) <= Math.pow(theme.anchorPointRadius,  2)) this.selectedPathSectionPoint = path.pathSections[i].p3;
            
            // If nothing was grabbed, continue searching through the PathSections
            if(this.selectedPathSectionPoint == undefined) continue;

            // Set up references to different parts of the path that need to be controlled in OnMouseMove
            this.selectedPathSection = path.pathSections[i];
            if(i > 0) this.selectedPrevPathSection = path.pathSections[i - 1];
            if(i < path.pathSections.length - 1) this.selectedNextPathSection = path.pathSections[i + 1];

            // Set reference to the selected PathSection
            this.selectedPathSection = path.pathSections[i];

            // Start updating the selectedPathSectionPoint's position in OnMouseMove
            this.draggingSelectedPathSectionPoint = true;

            // Something to grab was found, no need to continue searching
            break;
        }

        UpdateUI();
    },

    // Function that gets called whenever the left mouse button is released
    OnMouseUp(event) {
        // Stop dragging the currently selected point
        this.draggingSelectedPathSectionPoint = false;

        UpdateUI();
    },

    OnKeyDown(event) {
        if(event.key == "ArrowLeft") path.PrependPathSection();
        else if(event.key == "ArrowRight") path.AppendPathSection();
        else if(event.key == "ArrowDown" && this.selectedPathSection != undefined) path.SplitPathSection(this.selectedPathSection);
        else if(event.key == "Backspace" && this.selectedPathSection != undefined) {
            path.RemovePathSectionPoint(this.selectedPathSection, this.selectedPathSectionPoint);
            this.DeselectPathSection();
        }

        UpdateUI();
    },

    InitEventListeners() {
        // Set up the event listeners
        document.body.addEventListener("mousemove", (event) => {if(event.target == canvas) this.OnMouseMove(event)});
        document.body.addEventListener("mousedown", (event) => {if(event.target == canvas) this.OnMouseDown(event)});
        document.body.addEventListener("mouseup", (event) => {if(event.target == canvas) this.OnMouseUp(event)});
        document.body.addEventListener("keydown", (event) => {if(event.target == canvas) this.OnKeyDown(event)});
    },

    PrintControls() {
        let controls = [
            "Left arrow: Add new path section to start of path",
            "Right arrow: Add new path section to end of path",
            "Down arrow: Split selected path section",
            "Backspace: Delete selected path point"
        ];
        console.log(controls.join("\n"));
    }

};