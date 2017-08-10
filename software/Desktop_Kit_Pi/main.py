import serial
from serial import SerialException
import random
import time



#Initialized Serial Comm Locations, To Be Rearranged Later
node_addresses = [['/dev/ttyACM0'],
                ['/dev/ttyACM1', '/dev/ttyACM2'],
                ['/dev/ttyACM3', '/dev/ttyACM4'],
                ['/dev/ttyACM5', '/dev/ttyACM6']]

#Teensy ID's in Physical Locations
teensy_ids = [[0000000],
            [1363090,1293090],
            [1363240,1363370],
            [2456570,1411430]]

#Serial objects, Initialized as none until opened
serial_list = [[None],
            [None, None],
            [None, None],
            [None, None]]

#Communication Protocol Prefix and Suffix (Start and End of Message Bytes)
SOM_list = [b'\xff',b'\xee',b'\xdd']
EOM_list = [b'\xaa',b'\xbb',b'\xcc']

#State Machine Values
kStateActive = 0
kStateIdle = 1
kStateExcited = 2

#Timer Intervals
kIdleTimer = 15
backgroundTimer = 10

#Instruction Message Codes
INSTRUCT_CODE_LED_FADE_ANIMATION = b'\x0E'
INSTRUCT_CODE_GET_TEENSY_ID = b'\x00'
INSTRUCT_CODE_TEST_COMMUNICATION = b'\x01'

#Trigger Message Codes
TRIGGER_CODE_IR_THRESHOLD = b'\xFF'
TRIGGER_CODE_IR_LEFT_TO_RIGHT = b'\xFE'
TRIGGER_CODE_IR_RIGHT_TO_LEFT = b'\xFD'
TRIGGER_CODE_ENVELOPE_THRESHOLD = b'\xFC'


def waitUntilSerialPortsOpen():
    # only continue once we are able to open all serial ports
    print("Attempting to open serial ports...")
    while True:
        try:
            for i in range(len(serial_list)):
                for j in range(len(serial_list[i])):
                    serial_list[i][j] = serial.Serial(node_addresses[i][j],57600)
                    serial_list[i][j].flush()
                    serial_list[i][j].flushInput()
            break # if we are able to open all, break out of loop

        # catch the exception, wait one second before trying again
        except SerialException:
            time.sleep(1)
    print("Serial Ports Opened Sucessfully")

def rearrangeSerialPorts():

    new_node_addresses = list(node_addresses)

    for i in range(len(serial_list)):
        for j in range(len(serial_list[i])):
            sendMessage(INSTRUCT_CODE_TEST_COMMUNICATION)

            time.sleep(0.5)

            code, data, tid = checkIncomingMessageFromNode(i, j)
            for sublist in teensy_ids:
                if tid in sublist:
                    new_node_addresses[teensy_ids.index(sublist)][sublist.index(tid)] = node_addresses[i][j]

    node_addresses = new_node_addresses


def checkIncomingMessageFromNode(node_row, node_column):

    #Check if port has minimum message length in buffer
    if serial_list[node_row][node_column].inWaiting() >= 11:

        #Serial port for Target Node
        ser = serial_list[node_row][node_column]

        #Check for Start of Message
        for i in range(len(SOM_list)):
            current_SOM = ser.read()
            if current_SOM != SOM_list[i]:
                print("SOM Not Found, Flushing Input")
                print(current_SOM)
                ser.flushInput()
                return "error", "none", "none"
        
        #Teensy IDs, TODO: Use these for validation
        t1 = ser.read()
        t2 = ser.read()
        t3 = ser.read()

        received_tid = ((t1 << 16) | (t2 << 8)) | t3
        #Read in Length and Code
        message_length = ser.read()
        message_code = ser.read()

        #Find amount of bytes to read and store into data list
        num_bytes_to_receive = int.from_bytes(message_length, byteorder='big') - 8 - len(EOM_list);
        incoming_data = []

        if num_bytes_to_receive == 0:
            for i in range(len(EOM_list)):
                current_EOM = ser.read()
                if current_EOM != EOM_list[i]:
                    print("EOM Not Found")
                    ser.flushInput()
                    return "error", "none", "none"

            return message_code, [], received_tid

        else:

            if ser.inWaiting() >= num_bytes_to_receive:
                for i in range(num_bytes_to_receive):
                    incoming_data.append(ser.read())

        #Check for End of Message
            for i in range(len(EOM_list)):
                current_EOM = ser.read()
                if current_EOM != EOM_list[i]:
                    print("EOM Not Found")
                    ser.flushInput()
                    return "error", "none", "none"

        #Returns identifier byte for message code and relevant data list
            return message_code, incoming_data, received_tid


    else:

        return "none", "none", "none"

def handleIncomingMessageCode(incoming_message_code, incoming_data, node_row, node_column):

    #Handles message code depending on byte identifier
    if incoming_message_code == TRIGGER_CODE_IR_THRESHOLD:

        #Radially fades LEDs from triggered IR sensor

        #Expect first byte of corresponding message code to signify which IR was triggered
        ir_position = incoming_data[0]

        #Find position of IR in grid
        origin_row, origin_column = node_row, node_column*2 + int(ir_position)

        led_delay_timing_interval = 500

        #Send message to every node with waiting time before triggering LED fade animation
        for i in range(len(serial_list)):

            for j in range(len(serial_list[i])):

                #Taxicab Geometry Distance
                distance = abs((origin_row - i) + (origin_column - j))

                fade_startup_delay = [distance*led_delay_timing_interval]

                sendMessage(INSTRUCT_CODE_LED_FADE_ANIMATION, fade_startup_delay, i, j)
                sendMessage(INSTRUCT_CODE_LED_FADE_ANIMATION, fade_startup_delay, i, j)

    elif incoming_message_code == TRIGGER_CODE_IR_LEFT_TO_RIGHT:

        for i in range(len(serial_list)):

            for j in range(len(serial_list[i])):

                fade_startup_delay = [j]

                sendMessage(INSTRUCT_CODE_LED_FADE_ANIMATION, fade_startup_delay, i, j)
                sendMessage(INSTRUCT_CODE_LED_FADE_ANIMATION, fade_startup_delay, i, j)
    
    elif incoming_message_code == TRIGGER_CODE_IR_RIGHT_TO_LEFT:

        for i in range(len(serial_list)):

            for j in range(len(serial_list[i])):

                fade_startup_delay = [len(serial_list[i]) - j]

                sendMessage(INSTRUCT_CODE_LED_FADE_ANIMATION, fade_startup_delay, i, j)
                sendMessage(INSTRUCT_CODE_LED_FADE_ANIMATION, fade_startup_delay, i, j) 

    elif incoming_message_code == TRIGGER_CODE_ENVELOPE_THRESHOLD:

        print("TRIGGERED")

def sendMessage(outgoing_message_code, outgoing_data, node_row, node_column):
        # input:
        # outgoing_message_code: bytes object of length 1
        # outgoing_data: list of ints (can be empty), ASSUMES EACH ITEM CAN BE TRANSFORMED INTO ONE SINGLE BYTE EACH
        # node_row: int
        # node_column: int

        # first determine number of bytes to send
    messageLength = (len(SOM_list) # SOM
                  + 3 # teensy id
                  + 1 # length byte
                  + len(outgoing_message_code) # code
                  + len(outgoing_data) # outgoing data bytes
                  + len(EOM_list)) # EOM
                      
        # select serial port
    ser = serial_list[node_row][node_column]

    # send SOM (3 bytes)
    for SOM in SOM_list:
        ser.write(SOM)

    # send teensy id (3 bytes)
    TID_list = list((teensy_ids[node_row][node_column]).to_bytes(3, byteorder='big'))
    for TID in TID_list:
        ser.write(bytes([TID]))

    # send length (1 byte)
    ser.write(bytes([messageLength]))

    # send code (1 bytes)
    ser.write(outgoing_message_code)

    # send data
    for OUT in outgoing_data:
        ser.write(bytes([OUT]))

    # send EOM (3 bytes)
    for EOM in EOM_list:
        ser.write(EOM)

    #Print All Bytes

    print(SOM_list, end=" [")
    for tid in TID_list:
        print(bytes([tid]), end=", ")
    print("] [", end="")
    print(bytes([messageLength]), end="")
    print("] [", end="")
    print(outgoing_message_code, end="")
    print("] [", end="")
    for out in outgoing_data:
        print(bytes([out]), end=", ")
    print("]", end="")
    print(EOM_list)
    print(int.from_bytes(TID_list, byteorder='big'))
    print("\n")


def sendBackgroundCommand():

    for i in range(serial_list):
        for j in range(serial_list[i]):
            random_led_delay = random.randint(5,30)
            sendMessage(INSTRUCT_CODE_LED_FADE_ANIMATION, random_led_delay, i, j)


def main():

    global last_message_time
    global last_background_time
    global state
    state = kStateActive
    last_message_time = time.time()
    last_background_time = time.time()

    while True:
        try:

            current_time = time.time()

            if state == kStateActive:

                for node_row in range(len(serial_list)):
                    for node_column in range(len(serial_list[node_row])):
                        incoming_message_code, incoming_data, tid = checkIncomingMessageFromNode(node_row, node_column)

                        if incoming_message_code != "none":

                            last_message_time = time.time()

                            handleIncomingMessageCode(incoming_message_code, incoming_data, node_row, node_column)

                if current_time - last_message_time >= kIdleTimer:
                    state = kStateIdle

            elif state == kStateIdle:

                for node_row in range(len(serial_list)):
                    for node_column in range(len(serial_list[node_row])):
                        ser = serial_list[i][j]

                        if (ser.inWaiting()):
                            state = kStateActive

                        else:

                            if current_time - last_background_time >= backgroundTimer:
                                backgroundTimer = random.randint(5,30)
                                sendBackgroundCommand()

            elif state == kStateExcited:

                print("EXCITED!!!")

        except IOError:
            print("IOError, closing serial ports")

            for i in range(len(serial_list)):
                print ("Stopping" + str(node_addresses[count]))
                serial_list[i].close()

            waitUntilSerialPortsOpen()

        except KeyboardInterrupt:
            print("Closing Main Program and Serial Ports")

            for i in range(len(serial_list)):
                for j in range(len(serial.list[i])):
                    print ("Stopping" + str(node_addresses[i][j]))
                    serial_list[i][j].close()

            print("Completed")
            break

def test():

    # for i in range(len(serial_list)):
    #     for j in range(len(serial_list[i])):

    while True:

        try:

            for i in range(len(serial_list)):
                for j in range(len(serial_list[i])):

                    sendMessage(INSTRUCT_CODE_TEST_COMMUNICATION, [], i, j)

                    time.sleep(1)

                    # a, b = checkIncomingMessageFromNode(i, j)

                    # time.sleep(1)

                    # while a == "error":
                    #     print("ERROR")
                    #     sendMessage(INSTRUCT_CODE_TEST_COMMUNICATION, [], i, j)
                    #     time.sleep(0.5)
                    #     a, b = checkIncomingMessageFromNode(i, j)

                    # if a != "none":
                    #     print(node_addresses[i][j])
                    #     print(a)
                    #     print(b)
                    #     print('\n')

                    # if a == INSTRUCT_CODE_TEST_COMMUNICATION and b == []:
                    #     print(node_addresses[i][j] + ' PASSED')

                    if serial_list[i][j].inWaiting():

                        while serial_list[i][j].inWaiting():
                            print(serial_list[i][j].read())

        except KeyboardInterrupt:

            for i in range(len(serial_list)):
                for j in range(len(serial_list[i])):
                    print ("Stopping" + str(node_addresses[i][j]))
                    serial_list[i][j].close()

            print("Completed")
            break

if __name__ == '__main__':

    waitUntilSerialPortsOpen()
    print("Starting Main Program")
    test()
    # main()
