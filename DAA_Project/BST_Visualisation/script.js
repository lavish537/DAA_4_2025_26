class Node {
  constructor(value, x = 500, y = 50) {
    this.value = value;
    this.left = null;
    this.right = null;
    this.x = x;
    this.y = y;
    this.highlight = false;
  }
}

let root = null;
const svg = document.getElementById("treeCanvas");

function insert(root, value, x = 500, y = 50, depth = 0) {
  if (!root) return new Node(value, x, y);
  if (value < root.value) {
    root.left = insert(root.left, value, x - 200 / (depth + 1), y + 80, depth + 1);
  } else if (value > root.value) {
    root.right = insert(root.right, value, x + 200 / (depth + 1), y + 80, depth + 1);
  }
  return root;
}

function findMin(root) {
  while (root.left) root = root.left;
  return root;
}

function deleteNode(root, value) {
  if (!root) return null;
  if (value < root.value) root.left = deleteNode(root.left, value);
  else if (value > root.value) root.right = deleteNode(root.right, value);
  else {
    if (!root.left) return root.right;
    if (!root.right) return root.left;
    let minNode = findMin(root.right);
    root.value = minNode.value;
    root.right = deleteNode(root.right, minNode.value);
  }
  return root;
}

function drawTree(node) {
  if (!node) return;
  const radius = 25;

  // Draw node
  const circle = document.createElementNS("http://www.w3.org/2000/svg", "circle");
  circle.setAttribute("cx", node.x);
  circle.setAttribute("cy", node.y);
  circle.setAttribute("r", radius);
  circle.setAttribute("fill", node.highlight ? "gold" : "url(#grad)");
  circle.setAttribute("stroke", "#333");
  circle.setAttribute("stroke-width", "2");
  svg.appendChild(circle);

  const text = document.createElementNS("http://www.w3.org/2000/svg", "text");
  text.setAttribute("x", node.x);
  text.setAttribute("y", node.y + 5);
  text.setAttribute("text-anchor", "middle");
  text.setAttribute("fill", "white");
  text.setAttribute("font-weight", "bold");
  text.textContent = node.value;
  svg.appendChild(text);

  // Draw connectors
  if (node.left) {
    const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
    line.setAttribute("x1", node.x);
    line.setAttribute("y1", node.y + radius);
    line.setAttribute("x2", node.left.x);
    line.setAttribute("y2", node.left.y - radius);
    line.setAttribute("stroke", "#333");
    line.setAttribute("stroke-width", "2");
    svg.appendChild(line);
    drawTree(node.left);
  }
  if (node.right) {
    const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
    line.setAttribute("x1", node.x);
    line.setAttribute("y1", node.y + radius);
    line.setAttribute("x2", node.right.x);
    line.setAttribute("y2", node.right.y - radius);
    line.setAttribute("stroke", "#333");
    line.setAttribute("stroke-width", "2");
    svg.appendChild(line);
    drawTree(node.right);
  }
}

function renderTree() {
  svg.innerHTML = `
    <defs>
      <linearGradient id="grad" x1="0%" y1="0%" x2="100%" y2="100%">
        <stop offset="0%" style="stop-color:#4facfe;stop-opacity:1" />
        <stop offset="100%" style="stop-color:#0056b3;stop-opacity:1" />
      </linearGradient>
    </defs>
  `;
  drawTree(root);
}

function insertNode() {
  const val = document.getElementById("valueInput").value;
  if (val === "") return;
  root = insert(root, parseInt(val));
  renderTree();
  document.getElementById("valueInput").value = "";
}

function deleteNode() {
  const val = document.getElementById("valueInput").value;
  if (val === "") return;
  root = deleteNode(root, parseInt(val));
  renderTree();
  document.getElementById("valueInput").value = "";
}

function clearTree() {
  root = null;
  renderTree();
}

// Traversals
function inorder(node, result = []) {
  if (node) {
    inorder(node.left, result);
    result.push(node);
    inorder(node.right, result);
  }
  return result;
}
function preorder(node, result = []) {
  if (node) {
    result.push(node);
    preorder(node.left, result);
    preorder(node.right, result);
  }
  return result;
}
function postorder(node, result = []) {
  if (node) {
    postorder(node.left, result);
    postorder(node.right, result);
    result.push(node);
  }
  return result;
}

function traverse(type) {
  if (!root) return;
  let nodes = [];
  if (type === "inorder") nodes = inorder(root);
  if (type === "preorder") nodes = preorder(root);
  if (type === "postorder") nodes = postorder(root);

  document.getElementById("traversalOutput").textContent =
    type.charAt(0).toUpperCase() + type.slice(1) + ": " + nodes.map(n => n.value).join(" → ");

  let i = 0;
  const interval = setInterval(() => {
    nodes.forEach(n => n.highlight = false);
    if (i < nodes.length) {
      nodes[i].highlight = true;
      renderTree();
      i++;
    } else {
      clearInterval(interval);
    }
  }, 800);
}
