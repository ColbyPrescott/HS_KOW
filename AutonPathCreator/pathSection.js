class PathSection {
    constructor(p0, p1, p2, p3, startSpeed, endSpeed, code) {
        // First anchor point of the cubic bezier curve
        this.p0 = p0 || new Vec2(0, 0);
        // First control point of the cubic bezier curve
        this.p1 = p1 || new Vec2(3, 0);
        // Second control point of the cubic bezier curve
        this.p2 = p2 || new Vec2(6, 0);
        // Second anchor point of the cubic bezier curve
        this.p3 = p3 || new Vec2(9, 0);
        // Percent speed to target at the start of the curve
        this.startSpeed = startSpeed || 100;
        // Percent speed to target at the end of the curve
        this.endSpeed = endSpeed || 100;
        // C++ code to execute after driving the curve
        this.code = code || "";
    }

    // Get a point along the cubic bezier curve at percentage t
    GetPoint(t) {
        const q0 = Lerp(this.p0, this.p1, t);
        const q1 = Lerp(this.p1, this.p2, t);
        const q2 = Lerp(this.p2, this.p3, t)

        const r0 = Lerp(q0, q1, t);
        const r1 = Lerp(q1, q2, t);

        return Lerp(r0, r1, t);
    }

    DrawCurve() {
        ctx.lineWidth = theme.pathWidth;
        
        for(let i = 0; i < theme.pathQuality; i++) {
            const pointA = this.GetPoint((i + 0) / theme.pathQuality);
            const pointB = this.GetPoint((i + 1) / theme.pathQuality);
            ctx.beginPath();
            ctx.moveTo(pointA.x, pointA.y);
            ctx.lineTo(pointB.x, pointB.y);
            ctx.strokeStyle = `rgb(${
                // Luminence calculation derived from https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color
                Math.max(0, Lerp(-this.startSpeed, -this.endSpeed, i / theme.pathQuality)) / 100 / 0.299 * 0.587 * 255}, ${
                Math.max(0, Lerp(this.startSpeed, this.endSpeed, i / theme.pathQuality)) / 100 / 0.587 * 0.587 * 255}, ${
                this == input.selectedPathSection ? 150 : 0})`;
            ctx.stroke();
        }

        // Draw an arrow to show direction
        ctx.strokeStyle = theme.pathArrowColor;
        ctx.lineWidth = theme.pathArrowWidth;

        for(let i = 0; i < theme.pathArrowsPerSection; i++) {
            let pathPercent = 1 / (theme.pathArrowsPerSection + 1) * (i + 1);
            let arrowPoint = this.GetPoint(pathPercent);
            let arrowPointTowards = this.GetPoint(pathPercent + 0.01);
            let arrowAngle = Math.atan2(arrowPointTowards.y - arrowPoint.y, arrowPointTowards.x - arrowPoint.x);
            ctx.save();
            ctx.translate(arrowPoint.x, arrowPoint.y);
            ctx.rotate(arrowAngle);
            ctx.beginPath();
            ctx.moveTo(-theme.pathArrowSize, theme.pathArrowSize);
            ctx.lineTo(0, 0);
            ctx.lineTo(-theme.pathArrowSize, -theme.pathArrowSize);
            ctx.stroke();
            ctx.restore();
        }
    }

    DrawControlPoints() {
        // Draw lines from control points to their anchor points
        ctx.strokeStyle = theme.controlLineColor;
        ctx.lineWidth = theme.controlLineWidth;

        ctx.beginPath();
        ctx.moveTo(this.p0.x, this.p0.y);
        ctx.lineTo(this.p1.x, this.p1.y);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(this.p3.x, this.p3.y);
        ctx.lineTo(this.p2.x, this.p2.y);
        ctx.stroke();

        // Draw control points
        ctx.fillStyle = theme.controlPointColor;

        ctx.beginPath();
        ctx.arc(this.p1.x, this.p1.y, theme.controlPointRadius, 0, Math.PI * 2);
        ctx.fill();

        ctx.beginPath();
        ctx.arc(this.p2.x, this.p2.y, theme.controlPointRadius, 0, Math.PI * 2);
        ctx.fill();
    }

    DrawAnchorPoints() {
        ctx.fillStyle = theme.anchorPointColor;
        ctx.beginPath();
        ctx.arc(this.p0.x, this.p0.y, theme.anchorPointRadius, 0, Math.PI * 2);
        ctx.fill();

        if(this.code != "") {
            ctx.fillStyle = theme.codePointColor;
            ctx.beginPath();
            ctx.arc(this.p3.x, this.p3.y, theme.codePointRadius, 0, Math.PI * 2);
            ctx.fill();
        }

        ctx.fillStyle = theme.anchorPointColor;
        ctx.beginPath();
        ctx.arc(this.p3.x, this.p3.y, theme.anchorPointRadius, 0, Math.PI * 2);
        ctx.fill();
    }
}