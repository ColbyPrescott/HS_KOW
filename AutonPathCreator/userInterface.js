// Get the dynamic DOM elements
const domElements = {
    p0XInput: document.getElementById("p0XInput"),
    p0YInput: document.getElementById("p0YInput"),
    p1XInput: document.getElementById("p1XInput"),
    p1YInput: document.getElementById("p1YInput"),
    p2XInput: document.getElementById("p2XInput"),
    p2YInput: document.getElementById("p2YInput"),
    p3XInput: document.getElementById("p3XInput"),
    p3YInput: document.getElementById("p3YInput")
};

// Clear all of the inputs
function ClearUI() {
    domElements.p0XInput.value = "";
    domElements.p0YInput.value = "";
    domElements.p1XInput.value = "";
    domElements.p1YInput.value = "";
    domElements.p2XInput.value = "";
    domElements.p2YInput.value = "";
    domElements.p3XInput.value = "";
    domElements.p3YInput.value = "";
}

function UpdateUI() {
    // If nothing is selected, clear all the text
    if(input.selectedPathSection == undefined) {
        ClearUI();
        return;
    }

    // Set the text in each input field
    domElements.p0XInput.value = Math.round(input.selectedPathSection.p0.x * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
    domElements.p0YInput.value = Math.round(input.selectedPathSection.p0.y * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
    domElements.p1XInput.value = Math.round(input.selectedPathSection.p1.x * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
    domElements.p1YInput.value = Math.round(input.selectedPathSection.p1.y * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
    domElements.p2XInput.value = Math.round(input.selectedPathSection.p2.x * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
    domElements.p2YInput.value = Math.round(input.selectedPathSection.p2.y * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
    domElements.p3XInput.value = Math.round(input.selectedPathSection.p3.x * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
    domElements.p3YInput.value = Math.round(input.selectedPathSection.p3.y * Math.pow(10, theme.uiDecimals)) / Math.pow(10, theme.uiDecimals);
}

function OnEditUI(element) {
    // If nothing is selected, don't try to modify anything
    if(input.selectedPathSection == undefined) return;
    
    // Move the point that was modified and its related points
    if(element == domElements.p0XInput || element == domElements.p0YInput) input.MoveSelectedP0(new Vec2(parseFloat(domElements.p0XInput.value), parseFloat(domElements.p0YInput.value)));
    else if(element == domElements.p1XInput || element == domElements.p1YInput) input.MoveSelectedP1(new Vec2(parseFloat(domElements.p1XInput.value), parseFloat(domElements.p1YInput.value)));
    else if(element == domElements.p2XInput || element == domElements.p2YInput) input.MoveSelectedP2(new Vec2(parseFloat(domElements.p2XInput.value), parseFloat(domElements.p2YInput.value)));
    else if(element == domElements.p3XInput || element == domElements.p3YInput) input.MoveSelectedP3(new Vec2(parseFloat(domElements.p3XInput.value), parseFloat(domElements.p3YInput.value)));
}