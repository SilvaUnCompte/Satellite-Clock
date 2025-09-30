# Satellite Clock
**Satellite Clock** is an LED word clock that displays time using illuminated words instead of digital digits. The device automatically synchronizes with GPS satellites for precise timekeeping and falls back to NTP over WiFi when GPS is unavailable. It features a web-based configuration interface for easy setup and customization.

![IMG_20240217_141223](https://github.com/user-attachments/assets/4743ee36-cb9b-4934-b241-2f283d4cc874)

![20241104_195330~2](https://github.com/user-attachments/assets/10c6837e-6e05-46a8-84f4-6e2ec4651e7d)

## Features

- **Dual Time Source**: Primary GPS synchronization with NTP WiFi fallback
- **LED Word Display**: Time displayed using illuminated words (hours and minutes)
- **Web Configuration Interface**: Easy setup via browser dashboard
- **Automatic Time Updates**: Daily synchronization at 1:00 AM
- **Customizable Schedule**: Configure on/off times for automatic LED control
- **Timezone Support**: UTC offset configuration
- **Real-time Monitoring**: Satellite count and connection status via web interface

## Hardware Requirements

- **ESP32 WROVER Board** (or compatible ESP32 with sufficient GPIO pins)
- **GPS Module** connected to Serial2
- **LEDs** for word display (connected to specific GPIO pins)
- **WiFi Connection** for initial time sync and web interface
- **Wooden box** frame (optional, for aesthetic purposes)

![IMG_20240215_150541](https://github.com/user-attachments/assets/883b16bc-f70b-45b1-b1ae-4faf85adc2c8)

## Pin Configuration

The project uses 21 GPIO pins for LED control:
- **Hour LEDs**: Pins 33, 26, 13, 2, 1, 5, 25, 27, 12, 17, 16
- **Minute LEDs**: Pins 3, 23, 19, 21, 18, 22, 0
- **Special Indicators**: Pin 32 (midday), Pin 14 (midnight), Pin 4 (hour indicator)

## Installation & Setup

### 1. Hardware Setup
1. Connect your GPS module to ESP32 Serial2
2. Wire LEDs to the specified GPIO pins
3. Power the ESP32 board

### 2. Software Installation
1. Install [PlatformIO](https://platformio.org/) in VS Code
2. Clone this repository:
   ```bash
   git clone https://github.com/SilvaUnCompte/satellite-clock.git
   cd satellite-clock
   ```
3. Build and upload to your ESP32:
   ```bash
   pio run --target upload
   ```
4. Upload the web interface files:
   ```bash
   pio run --target uploadfs
   ```

### 3. Initial Configuration
1. The device creates a WiFi access point on first boot
2. Connect to the ESP32's WiFi network
3. Open your browser and navigate to the device's IP address
4. Configure your WiFi credentials and preferences:
   - **SSID & Password**: Your WiFi network credentials
   - **UTC Offset**: Your timezone offset from UTC
   - **Operation Hours**: Set when LEDs should be active (e.g., 7.0 to 23.0 for 7 AM to 11 PM)

## Usage

### Web Interface
Access the web dashboard to:
- Configure WiFi credentials
- Set timezone (UTC offset)
- Define operating hours
- Test WiFi connectivity
- Monitor GPS satellite count
- Update time synchronization

### Automatic Operation
- The clock automatically displays the current time using illuminated words
- Updates displayed every 10 seconds
- Synchronizes with GPS satellites when available (priority)
- Falls back to NTP over WiFi when GPS signal is weak
- Automatically updates time daily at 1:00 AM
- Respects configured on/off schedule

## Technical Details

### Libraries Used
- **TinyGPSPlus**: GPS data parsing
- **ESP Async WebServer**: Web interface
- **AsyncTCP**: Asynchronous TCP communication
- **SPIFFS**: File system for web assets

### Time Management
The system intelligently manages time sources:
1. **Primary**: GPS satellites (when satellite available)
2. **Fallback**: NTP over WiFi
3. **Offline**: Maintains time using ESP32's internal clock

### LED Control
- Word-based time display
- Automatic brightness control based on schedule
- Individual LED control for precise word illumination

## Configuration Options

All settings are stored in ESP32's NVRAM and persist across reboots:

| Setting | Description | Default |
|---------|-------------|---------|
| `ssid` | WiFi network name | - |
| `password` | WiFi password | - |
| `utc` | Timezone offset from UTC | 0 |
| `on_off` | Enable/disable LEDs | 1 (enabled) |
| `on_start` | LED start time (24h format) | 0.0 |
| `on_end` | LED end time (24h format) | 24.0 |

## API Endpoints

The web server provides REST API endpoints:
- `GET /` - Main dashboard
- `GET /get-config` - Retrieve current configuration
- `GET /update-config` - Update configuration parameters
- `GET /update-time` - Force time synchronization
- `GET /get-connection-status` - Check WiFi status
- `GET /get-satellite-count` - Get GPS satellite count

## Troubleshooting

### No Time Display
1. Check GPS module connection to Serial2
2. Verify WiFi credentials in web interface
3. Ensure device has internet access for NTP

### Web Interface Not Accessible
1. Check if device is connected to your WiFi network
2. Look for device IP in router's DHCP client list
3. Try connecting directly to device's access point

### LEDs Not Working
1. Verify GPIO pin connections
2. Check power supply capacity for all LEDs
3. Review pin configuration in `LEDManager.cpp`

## Contributing

Contributions are welcome! Please feel free to:
- Report bugs or issues
- Suggest new features
- Submit pull requests
- Improve documentation

## License

This project is open source. Please check the repository for [license details](LICENSE).

## Authors

- **SilvaUnCompte** - Initial work and development

---

**Note**: The LED arrangement and word patterns are optimized for French time representation but can be easily adapted for other languages.
