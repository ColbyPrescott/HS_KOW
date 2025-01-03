// Two numbers paired together to form a coordinate
class Vec2 {
    constructor(a, b) {
        // constructor(Vec2 a)
        if(a instanceof Vec2) {
            this.x = a.x;
            this.y = a.y;
        // constructor(number a, number b)
        } else {
            this.x = a || 0;
            this.y = b || 0;
        }
    }

    // Move this Vec2 by another Vec2
    Translate(vec) {
        this.x += vec.x;
        this.y += vec.y;

        return this;
    }

    // Rotate this Vec2 counter-clockwise around (0, 0)
    Rotate(radians) {
        const cos = Math.cos(radians);
        const sin = Math.sin(radians);
        const x = this.x;
        const y = this.y;

        this.x = cos * x - sin * y;
        this.y = sin * x + cos * y;
        
        return this;
    }

    // Scale the Vec2 toward or away from (0, 0) by a number or another Vec2
    Scale(a) {
        // Scale(Vec2 a)
        if(a instanceof Vec2) {
            this.x *= a.x;
            this.y *= a.y;
        // Scale(number a)
        } else {
            this.x *= a;
            this.y *= a;
        }

        return this;
    }
}

// Convert a number from one range to another
function Map(n, min1, max1, min2, max2) {
    return (n - min1) / (max1 - min1) * (max2 - min2) + min2;
}

// Linear interpolate between two points
function Lerp(a, b, t) {
    if(a instanceof Vec2) return new Vec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
    else return a + (b - a) * t;
}