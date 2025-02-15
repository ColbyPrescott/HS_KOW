class Ghost {
    // Array of all ghost objects
    static ghosts = [];

    constructor(driveLog) {
        // Turn the drive log into a list of vertices
        this.vertices = driveLog.split("\n");
        for(let i in this.vertices) {
            let nums = this.vertices[i].split(",").map(x => parseFloat(x || 0));

            if(nums.includes(NaN)) {
                alert("Could not convert the line:\n" + this.vertices[i]);;
                return;
            }

            this.vertices[i] = {
                x: nums[0],
                y: nums[1],
                rotation: nums[2]
            };
        }
    }

    Draw() {
        // Draw transparent circles on each point so that closer points
        // will appear darker and indicate a slower speed
        ctx.fillStyle = theme.ghostColor;

        for(let vertex of this.vertices) {
            ctx.beginPath();
            ctx.arc(vertex.x, vertex.y, theme.ghostWidth, 0, Math.PI * 2);
            ctx.fill();
        }
    }

    static DrawAllGhosts() {
        for(let ghost of Ghost.ghosts) ghost.Draw();
    }

}