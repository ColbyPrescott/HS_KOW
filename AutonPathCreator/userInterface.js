// Get the dynamic DOM elements
const domElements = {
    fieldSelect: document.getElementById("fieldSelect"),

    p3XInput: document.getElementById("p3XInput"),
    p0XInput: document.getElementById("p0XInput"),
    p0YInput: document.getElementById("p0YInput"),
    p1XInput: document.getElementById("p1XInput"),
    p1YInput: document.getElementById("p1YInput"),
    p2XInput: document.getElementById("p2XInput"),
    p2YInput: document.getElementById("p2YInput"),
    p3YInput: document.getElementById("p3YInput"),
    startSpeedInput: document.getElementById("startSpeedInput"),
    endSpeedInput: document.getElementById("endSpeedInput"),
    codeTextarea: document.getElementById("codeTextarea"),

    jsonTextarea: document.getElementById("jsonTextarea"),
    cppTextarea: document.getElementById("cppTextarea"),

    ghostTextarea: document.getElementById("ghostTextarea")
};

// Clear all of the point related inputs
function ClearPointUI() {
    domElements.p0XInput.value = "";
    domElements.p0YInput.value = "";
    domElements.p1XInput.value = "";
    domElements.p1YInput.value = "";
    domElements.p2XInput.value = "";
    domElements.p2YInput.value = "";
    domElements.p3XInput.value = "";
    domElements.p3YInput.value = "";
    domElements.startSpeedInput.value = "";
    domElements.endSpeedInput.value = "";
    domElements.codeTextarea.value = "";
}

// Clear all inputs
function ClearAllUI() {
    ClearPointUI();
    domElements.jsonTextarea.value = "";
    domElements.cppTextarea.value = "";
    domElements.ghostTextarea.value = "";
}

function UpdateUI() {
    // If nothing is selected, clear all the text
    if(input.selectedPathSection == undefined) {
        ClearPointUI();
    } else {
        // Set the text in each input field
        domElements.p0XInput.value = input.selectedPathSection.p0.x;
        domElements.p0YInput.value = input.selectedPathSection.p0.y;
        domElements.p1XInput.value = input.selectedPathSection.p1.x;
        domElements.p1YInput.value = input.selectedPathSection.p1.y;
        domElements.p2XInput.value = input.selectedPathSection.p2.x;
        domElements.p2YInput.value = input.selectedPathSection.p2.y;
        domElements.p3XInput.value = input.selectedPathSection.p3.x;
        domElements.p3YInput.value = input.selectedPathSection.p3.y;
        domElements.startSpeedInput.value = input.selectedPathSection.startSpeed;
        domElements.endSpeedInput.value = input.selectedPathSection.endSpeed;
        domElements.codeTextarea.value = input.selectedPathSection.code;
    }

    // Update the JSON textarea with the latest PathSection data
    jsonTextarea.value = JSON.stringify(path.pathSections);

    // Generate C++ code
    cppTextarea.value = "";
    if(path.pathSections.length > 0) {
        // Setup APS
        let start = path.pathSections[0];
        let startHeading = Math.atan2(start.p1.y - start.p0.y, start.p1.x - start.p0.x);
        if(startHeading < 0) startHeading = Math.PI * 2 + startHeading;
        
        cppTextarea.value += `aps.SetPosition(${start.p0.x}, ${start.p0.y});\n`;
        cppTextarea.value += `aps.SetRotation(${startHeading});\n`;
        cppTextarea.value += "aps.SetDriving(true);\n";

        // Body of the autonomous sequence
        for(let pathSection of path.pathSections) {
            cppTextarea.value += `aps.AddPathSection(${pathSection.p0.x}, ${pathSection.p0.y}, ${pathSection.p1.x}, ${pathSection.p1.y}, ${pathSection.p2.x}, ${pathSection.p2.y}, ${pathSection.p3.x}, ${pathSection.p3.y}, ${pathSection.startSpeed}, ${pathSection.endSpeed});\n`;
            if(pathSection.code == "") continue;

            cppTextarea.value += "aps.EndPath();\n";
            cppTextarea.value += pathSection.code + "\n";
        }

        // End path if needed
        if(path.pathSections[path.pathSections.length - 1].code == "") cppTextarea.value += "aps.EndPath();";
    }
}

function OnEditUI(element) {
    // Move the point that was modified and its related points
    if(input.selectedPathSection != undefined) {
        if(element == domElements.p0XInput || element == domElements.p0YInput) input.MoveSelectedP0(new Vec2(parseFloat(domElements.p0XInput.value), parseFloat(domElements.p0YInput.value)));
        else if(element == domElements.p1XInput || element == domElements.p1YInput) input.MoveSelectedP1(new Vec2(parseFloat(domElements.p1XInput.value), parseFloat(domElements.p1YInput.value)));
        else if(element == domElements.p2XInput || element == domElements.p2YInput) input.MoveSelectedP2(new Vec2(parseFloat(domElements.p2XInput.value), parseFloat(domElements.p2YInput.value)));
        else if(element == domElements.p3XInput || element == domElements.p3YInput) input.MoveSelectedP3(new Vec2(parseFloat(domElements.p3XInput.value), parseFloat(domElements.p3YInput.value)));
        else if(element == domElements.startSpeedInput) input.selectedPathSection.startSpeed = parseFloat(domElements.startSpeedInput.value) || 0;
        else if(element == domElements.endSpeedInput) input.selectedPathSection.endSpeed = parseFloat(domElements.endSpeedInput.value) || 0;
        else if(element == domElements.codeTextarea) input.selectedPathSection.code = domElements.codeTextarea.value;
    }

    // Convert the JSON input into PathSection objects
    if(element == domElements.jsonTextarea) {
        try {
            const jsonArray = JSON.parse(domElements.jsonTextarea.value);
            path.pathSections = [];
            for(let jsonPathSection of jsonArray) {
                path.pathSections.push(new PathSection(
                    new Vec2(jsonPathSection.p0.x, jsonPathSection.p0.y),
                    new Vec2(jsonPathSection.p1.x, jsonPathSection.p1.y),
                    new Vec2(jsonPathSection.p2.x, jsonPathSection.p2.y),
                    new Vec2(jsonPathSection.p3.x, jsonPathSection.p3.y),
                    jsonPathSection.startSpeed,
                    jsonPathSection.endSpeed,
                    jsonPathSection.code
                ));
            }
        } catch(err) {
            domElements.jsonTextarea.value = "Invalid JSON";
            return;
        }
    }

    // When a drive log is pastes, convert it into a ghost
    if(element == domElements.ghostTextarea) {
        Ghost.ghosts.push(new Ghost(domElements.ghostTextarea.value));

        // Clear textarea, the raw numbers aren't meant to mean much
        domElements.ghostTextarea.value = "";
    }

    // Since other points were moved as well, update the entire UI
    UpdateUI();
}