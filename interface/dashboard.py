import tkinter as tk
import serial
from tkinter import ttk
# Create the main window
root = tk.Tk()
root.title("Smart Greenhouse Dashboard")
root.geometry("2000x1000")  # Set window size
root.configure(bg='#AFE1AF')


# Define a label
label = ttk.Label(root, text="Smart Greenhouse Dashboard", font=("Helvetica", 20), background='#AFE1AF')
label.pack(pady=30)

# Define sensor data variables
temperature_var = tk.StringVar(value="Temperature: N/A")
humidity_var = tk.StringVar(value="Humidity: N/A")
water_level_var = tk.StringVar(value="Water Level: N/A")

# Add labels to display sensor data
temperature_label = ttk.Label(root, textvariable=temperature_var, font=("Helvetica", 18), background='#AFE1AF')
temperature_label.pack(pady=20)

humidity_label = ttk.Label(root, textvariable=humidity_var, font=("Helvetica", 18), background='#AFE1AF')
humidity_label.pack(pady=20)

water_level_label = ttk.Label(root, textvariable=water_level_var, font=("Helvetica", 18), background='#AFE1AF')
water_level_label.pack(pady=20)

# Define variables to track fan speeds
fan1_speed_var = tk.StringVar(value="Fan1 Speed: 0")
fan2_speed_var = tk.StringVar(value="Fan2 Speed: 0")

# Fan1 Speed Control (Using Slider)
def update_fan_speed(value):
    print(f"Fan1 speed set to {value}")
    # Send the fan speed to Arduino
    ser.write(f"FAN1_SPEED,{value}\n".encode())

fan1_speed_label = ttk.Label(root, text="Fan1 Speed", font=("Helvetica", 18), background='#AFE1AF')
fan1_speed_label.pack(pady=20)

fan1_speed_slider = ttk.Scale(root, from_=0, to=100, orient="horizontal", command=update_fan_speed, length=300)
fan1_speed_slider.pack(pady=30)

# Fan2 Speed Control (Using Slider)
def update_fan2_speed(value):
    print(f"Fan2 speed set to {value}")
    ##ser.write(f"FAN2_SPEED,{value}\n".encode())

fan2_speed_label = ttk.Label(root, text="Fan2 Speed", font=("Helvetica", 18), background='#AFE1AF')
fan2_speed_label.pack(pady=7)

fan2_speed_slider = ttk.Scale(root, from_=0, to=100, orient="horizontal", command=update_fan2_speed, length=300)
fan2_speed_slider.pack(pady=30)

# Define a variable to track the LED state
led_state = False  # Initially off

# Function to toggle and display the LED state
def toggle_led():
    global led_state
    led_state = not led_state  # Toggle the state (True -> False or False -> True)
    
    if led_state:
        print("LED is ON")
        led_button.config(text="Turn LED OFF")  # Update button text to indicate the next action
    else:
        print("LED is OFF")
        led_button.config(text="Turn LED ON")  # Update button text to indicate the next action

# Create the LED button
led_button = ttk.Button(root, text="Turn LED ON", command=toggle_led)
led_button.pack(pady=20, padx=20)
led_button.config(padding=(10, 10))

# Initialize serial connection (adjust COM port as needed)
##ser = serial.Serial('COM3', 9600, timeout=1)

##def read_sensor_data():
  ##  if ser.in_waiting > 0:
    ##    data = ser.readline().decode('utf-8').strip()
         
      ##  try:
        ##    temp, hum, water = data.split(',')
          ##  temperature_var.set(f"Temperature: {temp} °C")
            ## humidity_var.set(f"Humidity: {hum} %")
             ##water_level_var.set(f"Water Level: {water} %")
         ##except ValueError:
           ## print("Error parsing data:", data)  # Handle any parsing errors

    # Call again after 1000 ms (1 second)
     ##root.after(1000, read_sensor_data)

# Start reading sensor data
 ##read_sensor_data()

# Start the Tkinter main loop
root.mainloop() 
