# TODO List
## OLED_DISPLAY
### WriteMessage function
1. Format messages so they go right if the user sent the message and left if it was sent by someone else (using a 1 or 0 at the beginning of the buffer)
2. AutoScroll when a new message arrives

### ShowDisplay function
1. Show messages right or left depending on who wrote it

### ScrollUp & ScrollDown function
1. Before scrolling, pull messages in batches from disk

## LORA
### Encrypt and Decrypt functions
1. Decide to use RSA, AES or XOR algorithms

### Message Formatting
1. Format messages with headers (id of sender, nodes visited...)

### Optimize function
1. Optimize all parameters

### GetSignalQuality function
1. Create signal quality getter for the main to use it

## SD_CONTROLLER
1. Start it

## KEYBOARD_CONTROLLER
1. Start it
2. Register multipull keystrokes (memory so that the controller gives the final char to the main)

## SPEAKER
1. Read tone from disk when message arrives

## MAIN
1. Graphics processing in the secondary core
2. Clock and batery percentage polling 
3. 
