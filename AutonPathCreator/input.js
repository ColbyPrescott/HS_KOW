// Container object to hold variables related to mouse input
const mouse = {
    // Current position of the mouse in field coordinate space
    position: new Vec2(),

    // Reference to the position of the object that is currently being held
    heldObject: undefined,

    // Function that gets called whenever the mouse moves
    OnMouseMove(event) {
        // Update mouse position, converting screen coordinates to the canvas's field coordinates
        this.position.x = Map(event.clientX, 0, canvas.width, 0, fieldSize.x);
        this.position.y = Map(event.clientY, 0, canvas.height, fieldSize.y, 0);

        // Update position of the held object
        if(this.heldObject == undefined) return;
        this.heldObject.x = this.position.x;
        this.heldObject.y = this.position.y;
    },

    // Function that gets called whenever the left mouse button is pressed down
    OnMouseDown(event) {
        // Loop through every vertex in the path and grab the first one that intersects the mouse
        for(let pathSection of path.pathSections) for(let vertex of [pathSection.p0, pathSection.p1, pathSection.p2, pathSection.p3]) {
            if(Math.pow(this.position.x - vertex.x, 2) + Math.pow(this.position.y - vertex.y, 2) <= Math.pow(2, 2)) {
                this.heldObject = vertex;
                break;
            }
        }
    },

    // Function that gets called whenever the left mouse button is released
    OnMouseUp(event) {
        // Release the currently heldObject
        this.heldObject = undefined;
    }

};

// Set up the event listeners
document.body.addEventListener("mousemove", (event) => {mouse.OnMouseMove(event);});
document.body.addEventListener("mousedown", (event) => {mouse.OnMouseDown(event);});
document.body.addEventListener("mouseup", (event) => {mouse.OnMouseUp(event);});

document.body.addEventListener("keydown", (event) => {if(event.key == " ") path.AddPathSection();});