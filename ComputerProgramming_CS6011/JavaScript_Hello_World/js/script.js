var head = document.head;

document.title = "Hello";

document.body.style.backgroundColor = "red";

var paragraph = document.createElement("P");
paragraph.innerHTML = "This is a paragraph.";
document.getElementById("newDiv").appendChild(paragraph);

var button = document.createElement("button");
button.innerHTML = "button";
document.body.appendChild(button);

var text = document.createElement("P");
text.innerHTML = "test";
button.onclick = function(){document.body.appendChild(text)};