# Cubong Examples

This document provides detailed descriptions of all example sketches included with the Cubong library.

## Example Overview

The library includes 10 example sketches demonstrating various features:

1. **TestTensore** - Basic tensor system test
2. **Miss** - Text display demonstration
3. **RiempiCubo** - Random filling animation
4. **SfogliaLed** - Individual LED scanning
5. **SfogliaPiani** - Layer cycling
6. **SfogliaPiani_Vuoto** - Empty layer cycling
7. **SfogliaPiani_input** - Interactive layer cycling
8. **StampaTensore** - Tensor pattern demonstration
9. **StampaTensore_Piani** - Layer-by-layer pattern building
10. **LampeggiaCubo_Input** - Interactive blinking

---

## TestTensore

**File:** `examples/TestTensore/TestTensore.ino`

### Description
This example demonstrates the basic tensor system functionality. It tests the tensor-to-buffer conversion and display functions.

### Features Demonstrated
- Tensor initialization
- Adding LEDs to the tensor using `add()`
- Converting tensor to buffer
- Displaying patterns on the cube

### Hardware
- Standard Cubong setup with 3 control pins (data=7, latch=6, clock=5)

### Code Highlights
```cpp
test.testTensore();
```

The `testTensore()` method cycles through different patterns, displaying them for 5 seconds each.

---

## Miss

**File:** `examples/Miss/Miss.ino`

### Description
Displays the word "MISS" on the cube with variable positioning controlled by an analog input (potentiometer).

### Features Demonstrated
- Text display functions (`letteraM()`, `letteraI()`, `letteraS()`)
- Analog input reading for interactive control
- Letter positioning in 3D space

### Hardware
- Standard Cubong setup (data=7, latch=6, clock=5)
- Potentiometer connected to analog pin A0

### How It Works
1. Reads analog input value (0-1023)
2. Maps input to position (0-4)
3. Displays each letter 20 times before moving to the next
4. Repeats sequence: M → I → S → S

### User Interaction
Turn the potentiometer to change the position of the letters in the cube.

---

## RiempiCubo

**File:** `examples/RiempiCubo/RiempiCubo.ino`

### Description
Creates an animation that fills the cube randomly, one LED at a time, creating a "filling" effect.

### Features Demonstrated
- Random LED selection
- Sequential LED activation
- The `riempiCubo()` function

### Hardware
- Standard Cubong setup with 4 control pins (data=7, latch=6, clock=5, enable=4)

### Animation Pattern
- Randomly selects a column (x, y position)
- Fills that column from bottom to top (z=0 to z=4)
- Adds a 15ms delay between each LED for visual effect
- Repeats indefinitely

---

## SfogliaLed

**File:** `examples/SfogliaLed/SfogliaLed.ino`

### Description
Scans through all 125 LEDs in the cube sequentially, creating a scanning effect.

### Features Demonstrated
- Triple nested loop for 3D scanning
- Individual LED control using `led()`
- Sequential activation pattern

### Hardware
- Standard Cubong setup

### Scanning Pattern
The sketch scans in this order:
1. Through all layers (z: 0→4)
2. For each layer, through all rows (i: 0→4)
3. For each row, through all columns (j: 0→4)

Each LED stays on for 100ms before moving to the next.

---

## SfogliaPiani

**File:** `examples/SfogliaPiani/SfogliaPiani.ino`

### Description
Demonstrates layer control by cycling through all five layers of the cube, building each layer LED by LED.

### Features Demonstrated
- Layer filling using tensor and `stampaPiano()`
- Progressive layer building
- Layer-by-layer display

### Hardware
- Standard Cubong setup with 4 control pins

### Animation Pattern
1. For each layer (k: 0→4):
   - Fill the layer LED by LED
   - Display each progressive state
   - 100ms delay per LED
2. Clear and repeat

---

## SfogliaPiani_Vuoto

**File:** `examples/SfogliaPiani_Vuoto/SfogliaPiani_Vuoto.ino`

### Description
Similar to SfogliaPiani but starts with empty layers and cycles through them.

### Features Demonstrated
- Layer activation using `piano()`
- Simple layer cycling
- Minimal code example

### Hardware
- Standard Cubong setup

### Animation Pattern
Cycles through layers 0-4 with a 500ms delay between each layer, keeping each layer fully lit when active.

---

## SfogliaPiani_input

**File:** `examples/SfogliaPiani_input/SfogliaPiani_input.ino`

### Description
Interactive layer cycling where the speed is controlled by an analog input (potentiometer).

### Features Demonstrated
- Analog input for interactive control
- Variable delay based on user input
- Layer cycling with `piano()`

### Hardware
- Standard Cubong setup
- Potentiometer on analog pin A0

### How It Works
1. Reads analog value from A0
2. Maps value to delay (0-1000ms)
3. Cycles through layers with calculated delay

### User Interaction
Adjust the potentiometer to control the speed of layer cycling.

---

## StampaTensore

**File:** `examples/StampaTensore/StampaTensore.ino`

### Description
Demonstrates the tensor system by creating patterns and displaying them on the cube.

### Features Demonstrated
- Tensor manipulation
- The `stampaPiano()` function
- Pattern creation

### Hardware
- Standard Cubong setup with 4 control pins

### Pattern
Creates a specific pattern using the tensor system and displays it layer by layer.

---

## StampaTensore_Piani

**File:** `examples/StampaTensore_Piani/StampaTensore_Piani.ino`

### Description
Shows how to build complex patterns layer by layer using the tensor system.

### Features Demonstrated
- Layer-by-layer pattern construction
- Tensor `add()` method
- Progressive pattern building
- Tensor clearing with `azzeraTensore()`

### Hardware
- Standard Cubong setup with 4 control pins

### Animation Pattern
1. For each layer (k: 0→4):
   - For each position in the layer:
     - Add LED to tensor: `add(i, j, k)`
     - Display the layer: `stampaPiano(k)`
     - 100ms delay
2. Clear tensor and repeat

This creates a visual effect of each layer being built up LED by LED.

---

## LampeggiaCubo_Input

**File:** `examples/LampeggiaCubo_Input/LampeggiaCubo_Input.ino`

### Description
Demonstrates the blinking/flashing functionality with variable delay controlled by analog input.

### Features Demonstrated
- The `lampeggiaCubo()` function
- Analog input for interactive control
- Blinking patterns

### Hardware
- Standard Cubong setup
- Potentiometer on analog pin A0

### How It Works
1. Reads analog input
2. Maps to delay value
3. Blinks the cube with the specified delay
4. Displays timing information on Serial monitor

### User Interaction
Adjust the potentiometer to change the blinking speed.

---

## Running the Examples

### Basic Steps

1. Open Arduino IDE
2. Go to **File** → **Examples** → **Cubong** → [Example Name]
3. Select your Arduino board: **Tools** → **Board**
4. Select the correct port: **Tools** → **Port**
5. Upload the sketch to your Arduino
6. Observe the pattern on your LED cube!

### Troubleshooting

**No LEDs lighting up:**
- Check your wiring connections
- Verify power supply is adequate
- Check that pin numbers match your hardware setup

**Flickering or dim LEDs:**
- May need to increase refresh rate
- Check power supply capacity
- Verify resistor values are appropriate

**Only some layers working:**
- Check layer control pins (l0-l4)
- Verify ULN2003 connections
- Test each layer pin individually

### Modifying Examples

All examples can be modified to fit your specific hardware configuration. Key parameters to adjust:

- **Pin numbers** in the Cubong constructor
- **Delay values** for animation speed
- **Pattern coordinates** for custom designs
- **Analog input pins** for interactive examples

### Creating Your Own Patterns

Use these examples as templates:
1. Start with **TestTensore** for basic tensor usage
2. Use **StampaTensore_Piani** to build layer-by-layer
3. Check **Miss** for text patterns
4. Study **RiempiCubo** for random animations

---

## Example Complexity Levels

### Beginner
- **SfogliaPiani_Vuoto** - Simplest example, just layer cycling
- **RiempiCubo** - Simple random filling

### Intermediate
- **SfogliaLed** - Triple nested loops
- **StampaTensore_Piani** - Tensor manipulation
- **SfogliaPiani** - Progressive building

### Advanced
- **Miss** - Text display and positioning
- **LampeggiaCubo_Input** - Complex timing and input
- **TestTensore** - Full tensor system demonstration

---

## Additional Resources

For more information:
- See the main [README.md](../README.md) for API reference
- Check [README_IT.md](../README_IT.md) for Italian documentation
- Review the source code in `Cubong.cpp` for implementation details

Happy coding! 🎨💡
