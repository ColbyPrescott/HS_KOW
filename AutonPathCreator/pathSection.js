class PathSection {
    constructor() {
        // First anchor point of the cubic bezier curve
        this.p0 = new Vec2(0, 0);
        // First control point of the cubic bezier curve
        this.p1 = new Vec2(24, 0);
        // Second control point of the cubic bezier curve
        this.p2 = new Vec2(24, 24);
        // Second anchor point of the cubic bezier curve
        this.p3 = new Vec2(0, 24);
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
        ctx.strokeStyle = theme.pathColor;
        ctx.lineWidth = theme.pathWidth;

        ctx.beginPath();
        ctx.moveTo(this.p0.x, this.p0.y);
        for(let i = 0; i <= theme.pathQuality; i++) {
            const point = this.GetPoint(i / theme.pathQuality);
            ctx.lineTo(point.x, point.y);
        }
        ctx.stroke();
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

        ctx.beginPath();
        ctx.arc(this.p3.x, this.p3.y, theme.anchorPointRadius, 0, Math.PI * 2);
        ctx.fill();
    }
}