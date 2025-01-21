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

    jsonTextarea: document.getElementById("jsonTextarea"),
    cppTextarea: document.getElementById("cppTextarea")
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
}

// Clear all inputs
function ClearAllUI() {
    ClearPointUI();
    domElements.jsonTextarea.value = "";
    domElements.cppTextarea.value = "";
}

function UpdateUI() {
    // If nothing is selected, clear all the text
    if(input.selectedPathSection == undefined) {
        ClearPointUI();
    } else {
        // Set the text in each input field
        domElements.p0XInput.value = Math.round(input.selectedPathSection.p0.x * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
        domElements.p0YInput.value = Math.round(input.selectedPathSection.p0.y * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
        domElements.p1XInput.value = Math.round(input.selectedPathSection.p1.x * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
        domElements.p1YInput.value = Math.round(input.selectedPathSection.p1.y * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
        domElements.p2XInput.value = Math.round(input.selectedPathSection.p2.x * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
        domElements.p2YInput.value = Math.round(input.selectedPathSection.p2.y * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
        domElements.p3XInput.value = Math.round(input.selectedPathSection.p3.x * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
        domElements.p3YInput.value = Math.round(input.selectedPathSection.p3.y * Math.pow(10, theme.decimals)) / Math.pow(10, theme.decimals);
    }

    // Update the JSON textarea with the latest PathSection data
    jsonTextarea.value = JSON.stringify(path.pathSections);
}

function OnEditUI(element) {
    // Move the point that was modified and its related points
    if(input.selectedPathSection != undefined) {
        if(element == domElements.p0XInput || element == domElements.p0YInput) input.MoveSelectedP0(new Vec2(parseFloat(domElements.p0XInput.value), parseFloat(domElements.p0YInput.value)));
        else if(element == domElements.p1XInput || element == domElements.p1YInput) input.MoveSelectedP1(new Vec2(parseFloat(domElements.p1XInput.value), parseFloat(domElements.p1YInput.value)));
        else if(element == domElements.p2XInput || element == domElements.p2YInput) input.MoveSelectedP2(new Vec2(parseFloat(domElements.p2XInput.value), parseFloat(domElements.p2YInput.value)));
        else if(element == domElements.p3XInput || element == domElements.p3YInput) input.MoveSelectedP3(new Vec2(parseFloat(domElements.p3XInput.value), parseFloat(domElements.p3YInput.value)));
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
                    new Vec2(jsonPathSection.p3.x, jsonPathSection.p3.y)
                ));
            }
        } catch(err) {
            domElements.jsonTextarea.value = "Invalid JSON";
        }
    }

    // Since other points were moved as well, update the entire UI
    UpdateUI();
}