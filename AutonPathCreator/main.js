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
ClearUI();

// Setup different inputs to trigger their functions
input.InitEventListeners();



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

    // Clear the background, stopping frames from being rendered on top of each other
    ctx.fillStyle = "#000000";
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    path.Draw();
}
window.requestAnimationFrame(Frame);