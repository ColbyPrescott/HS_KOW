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

    // Turn the displayed path into C++ code
    cppTextarea.value = converter.Generate();
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

    // Turn the C++ code into the displayed path
    if(element == domElements.cppTextarea) converter.Read(domElements.cppTextarea.value);

    // When a drive log is pastes, convert it into a ghost
    if(element == domElements.ghostTextarea) {
        Ghost.ghosts.push(new Ghost(domElements.ghostTextarea.value));

        // Clear textarea, the raw numbers aren't meant to mean much
        domElements.ghostTextarea.value = "";
    }

    // Since other points were moved as well, update the entire UI
    UpdateUI();
}