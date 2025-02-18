const converter = {
    // Number of spaces in a tab
    tabSpaces: 4,

    // C++ code in the file that comes before the APS code
    cppPreAPS: "",
    // C++ code in the file that comes after the APS code
    cppPostAPS: "",

    Read(inputCPP) {
        let lines = inputCPP.split("\n");
        
        let i = 0;

        // Put lines into cppPreAPS
        this.cppPreAPS = "";
        for(i = i; i < lines.length; i++) {
            if(lines[i].includes("aps.SetPosition(")) break;
            if(lines[i] == "}") break;
            this.cppPreAPS += lines[i] + "\n";
        }
        this.cppPreAPS = this.cppPreAPS.substring(0, this.cppPreAPS.length - 1); // Remove last \n

        // Skip setting up APS
        if(inputCPP.includes("aps.SetPosition(")) i += 3;

        // Put lines into path
        path.pathSections = [];
        for(i = i; i < lines.length; i++) {
            if(lines[i] == "}") break;

            // Get the numbers from the "   aps.AddPathSection(...);" line
            let nums = lines[i].substring(lines[i].indexOf("(") + 1, lines[i].length - 2).split(",").map(x => parseFloat(x));

            // Get the attatched code segment by stepping forward lines until the next PathSection is reached
            let attatchedCode = "";
            for(i = i + 1; i < lines.length; i++) {
                if(lines[i].includes("aps.AddPathSection(")) break;
                if(lines[i] == "}") break;
                if(lines[i].includes("aps.EndPath();")) continue;

                attatchedCode += lines[i].substring(this.tabSpaces) + "\n";
            }
            i--;
            if(attatchedCode.length > 0) attatchedCode = attatchedCode.substring(0, attatchedCode.length - 1); // Remove last \n
            
            // Turn the collected information into PathSection
            path.pathSections.push(new PathSection(
                new Vec2(nums[0], nums[1]),
                new Vec2(nums[2], nums[3]),
                new Vec2(nums[4], nums[5]),
                new Vec2(nums[6], nums[7]),
                nums[8],
                nums[9],
                attatchedCode
            ));
        }

        // Put remaining lines into cppPostAPS
        this.cppPostAPS = "";
        for(i = i; i < lines.length; i++) {
            this.cppPostAPS += lines[i] + "\n";
            this.cppPostAPS = this.cppPostAPS.substring(0, this.cppPostAPS.length - 1); // Remove last \n
        }
    },

    Generate() {
        // Start string with cppPreAPS
        let outputCPP = this.cppPreAPS;
        outputCPP += "\n";

        // Generate APS section of C++ code
        if(path.pathSections.length > 0) {
            // Setup APS
            let start = path.pathSections[0];
            let startHeading = Math.atan2(start.p1.y - start.p0.y, start.p1.x - start.p0.x);
            if(startHeading < 0) startHeading = Math.PI * 2 + startHeading;
            
            outputCPP += `${' '.repeat(this.tabSpaces)}aps.SetPosition(${start.p0.x}, ${start.p0.y});\n`;
            outputCPP += `${' '.repeat(this.tabSpaces)}aps.SetRotation(${startHeading});\n`;
            outputCPP += `${' '.repeat(this.tabSpaces)}aps.SetDriving(true);\n`;

            // Body of the autonomous sequence
            for(let pathSection of path.pathSections) {
                outputCPP += `${' '.repeat(this.tabSpaces)}aps.AddPathSection(${pathSection.p0.x}, ${pathSection.p0.y}, ${pathSection.p1.x}, ${pathSection.p1.y}, ${pathSection.p2.x}, ${pathSection.p2.y}, ${pathSection.p3.x}, ${pathSection.p3.y}, ${pathSection.startSpeed}, ${pathSection.endSpeed});\n`;
                if(pathSection.code == "") continue;

                outputCPP += `${' '.repeat(this.tabSpaces)}aps.EndPath();\n`;
                outputCPP += `${' '.repeat(this.tabSpaces)}${pathSection.code.replaceAll("\n", `\n${' '.repeat(this.tabSpaces)}`)}\n`;
            }

            // End path if needed
            if(path.pathSections[path.pathSections.length - 1].code == "") outputCPP += `${' '.repeat(this.tabSpaces)}aps.EndPath();`;
        }

        // End string with cppPostAPS;
        if(outputCPP[outputCPP.length - 1] != "\n") outputCPP += "\n";
        outputCPP += this.cppPostAPS;

        return outputCPP;
    }

};