import { SVG, Line } from '@svgdotjs/svg.js';

export function Draw() {
  const draw = SVG().addTo('#canvas').size(800, 600);
  const lines: Line[] = [];
  let isDrawing = false;
  let startX: number = 0;
  let startY: number = 0;
  let selectedLine: Line | null = null;
  let selectedEndpoint: 'start' | 'end' | null = null;

  // Function to calculate distance between two points
  const distance = (x1: number, y1: number, x2: number, y2: number) => {
    const dx = x2 - x1;
    const dy = y2 - y1;
    return Math.sqrt(dx * dx + dy * dy);
  };

  // Function to check if a point is close to a line endpoint
  const isCloseToEndpoint = (x: number, y: number, line: Line) => {
    const tolerance = 5; // Adjust this value to set the proximity tolerance
    return (
      distance(x, y, line.attr('x1'), line.attr('y1')) < tolerance ||
      distance(x, y, line.attr('x2'), line.attr('y2')) < tolerance
    );
  };

  const onMouseDown = (event: MouseEvent) => {
    const { offsetX, offsetY, button, altKey, ctrlKey, metaKey } = event;
    selectedLine = null;
    selectedEndpoint = null;

    for (const line of lines) {
      if (isCloseToEndpoint(offsetX, offsetY, line)) {
        // If any of these keys are held, we want to move the existing lines instead of drawing a
        // new one
        if (altKey || ctrlKey || metaKey) {
          selectedLine = line;
          selectedEndpoint =
            distance(offsetX, offsetY, line.attr('x1'), line.attr('y1')) <
            distance(offsetX, offsetY, line.attr('x2'), line.attr('y2'))
              ? 'start'
              : 'end';
        }
        break;
      }
    }

    if (!selectedLine) {
      // Start drawing a new line if not near an existing endpoint
      isDrawing = true;
      startX = offsetX;
      startY = offsetY;
      const newLine = draw
        .line(startX, startY, startX, startY)
        .stroke({ width: 2, color: 'black' });
      lines.push(newLine);
    }
  };

  const onMouseMove = (event: MouseEvent) => {
    const { offsetX, offsetY } = event;

    if (isDrawing && lines.length > 0) {
      const currentLine = lines[lines.length - 1];
      currentLine.plot(startX, startY, offsetX, offsetY);
    } else if (selectedLine && selectedEndpoint) {
      // Move the selected endpoint
      if (selectedEndpoint === 'start') {
        selectedLine.plot(offsetX, offsetY, selectedLine.attr('x2'), selectedLine.attr('y2'));
      } else {
        selectedLine.plot(selectedLine.attr('x1'), selectedLine.attr('y1'), offsetX, offsetY);
      }
    }
  };

  const onMouseUp = () => {
    isDrawing = false;
    selectedLine = null;
    selectedEndpoint = null;
  };

  draw.node.addEventListener('mousedown', onMouseDown);
  draw.node.addEventListener('mousemove', onMouseMove);
  draw.node.addEventListener('mouseup', onMouseUp);
}

document.addEventListener('DOMContentLoaded', Draw);
