// Size of the field in inches
const fieldSize = new Vec2(24 * 6, 24 * 6);

// Set up canvas
// Canvas element that can be drawn on
const canvas = document.getElementById("mainCanvas");
// The rendering context that contains canvas draw functions
const ctx = canvas.getContext("2d");

// Ensure that the canvas always scales to fit the screen
function ResizeCanvas() {
    // Update size to fill as much of the screen as possible while remaining square
    canvas.width = Math.min(window.innerWidth, window.innerHeight);
    canvas.height = Math.min(window.innerWidth, window.innerHeight);

    // Transform coordinate space so that (0, 0) is the bottom left in order to match the rest of the APS system
    ctx.reset();
    ctx.scale(canvas.width / fieldSize.x, -canvas.height / fieldSize.y);
    ctx.translate(0, -fieldSize.y);

    // Update whether the sidePanel is to the right or bottom of the canvas
    document.getElementById("splitPanel").style.flexDirection = (window.innerWidth > window.innerHeight) ? "row" : "column";
}
window.addEventListener("resize", ResizeCanvas);
ResizeCanvas();

// Don't let the browser cache the input values beween page refreshes
ClearAllUI();

// Setup different inputs to trigger their functions
input.InitEventListeners();

// In case the controls are ever forgotten, make them easy to read in the console
input.PrintControls();



// Set up main ticking loop
// The number of seconds between the last frame and now
let deltaTime;
// Temporary variable to calculate deltaTime
let frameStartTime = Date.now();
function Frame() {
    // Update deltaTime
    deltaTime = (Date.now() - frameStartTime) / 1000;
    frameStartTime = Date.now();
    // Schedule Frame() to be run again
    window.requestAnimationFrame(Frame);

    // Draw the field as the image that stops frames from drawing on top of each other
    ctx.drawImage(document.getElementById(domElements.fieldSelect.value), 0, 0, fieldSize.x, fieldSize.y);

    path.Draw();
}
window.requestAnimationFrame(Frame);