# Script to create Word documentation for the project

$docPath = "c:\Users\teodo\Desktop\Proiect SI\embedded-systems-course-atmega328p\DOCUMENTATIE_PROIECT.docx"
$word = New-Object -ComObject Word.Application
$doc = $word.Documents.Add()
$selection = $word.Selection

# Helper function to add heading
function Add-Heading {
    param([string]$text, [int]$level = 1)
    $sizes = @(28, 16, 14, 12, 11)
    $selection.Font.Size = $sizes[$level - 1]
    $selection.Font.Bold = $true
    $selection.TypeText($text)
    $selection.TypeParagraph()
    $selection.Font.Bold = $false
    $selection.Font.Size = 11
}

function Add-Text {
    param([string]$text, [bool]$bold = $false)
    $selection.Font.Bold = $bold
    $selection.TypeText($text)
    $selection.TypeParagraph()
}

# Title
$selection.Font.Size = 28
$selection.Font.Bold = $true
$selection.TypeText("DOCUMENTAȚIE PROIECT")
$selection.TypeParagraph()
$selection.Font.Size = 14
$selection.Font.Bold = $false
$selection.TypeText("Sistem de Control Volan - ATmega328P")
$selection.TypeParagraph()
$selection.TypeParagraph()

# Date and info
$selection.Font.Size = 11
$date = Get-Date -Format "dd.MM.yyyy"
Add-Text "Data: $date"
Add-Text "Platformă: Arduino Nano/Uno"
Add-Text "Microcontroller: ATmega328P"
$selection.TypeParagraph()

# Section 1: Overview
Add-Heading "1. DESCRIERE GENERALĂ"
Add-Text "Acest proiect implementează un sistem de control pentru volan electronic (steering wheel controller) pe microcontroller ATmega328P (Arduino Nano/Uno). Sistemul permite controlul vitezelor (gear shifting) și afișarea informațiilor în timp real."
$selection.TypeParagraph()

# Section 2: Features
Add-Heading "2. CARACTERISTICI PRINCIPALE" 2
$features = @(
    "Afișaj 7-segmente (MAX7219) - Afișează viteza și treapta curentă",
    "LED RGB WS2812 (16 LED-uri) - Indicator RPM cu codare pe culori",
    "Paddle shifter (2 butoane) - Urcare/Coborâre trepte de viteză",
    "Butoane 12mm (2 butoane) - Intrări utilizator suplimentare",
    "Butoane 7mm (8 butoane) - Interfață extensibilă",
    "Encodere rotative - Intrări analogice",
    "Timer0 - Sistem de timers cu tick de 1ms",
    "Interrupt extern (INT0, INT1) - Suport pentru întreruperi externe",
    "EEPROM - Memorie persistentă",
    "ADC - Conversie analog-digitală",
    "USART - Comunicație serială",
    "PWM - Generare semnale PWM"
)

foreach ($feature in $features) {
    Add-Text "• $feature"
}
$selection.TypeParagraph()

# Section 3: Architecture
Add-Heading "3. ARHITECTURA PROIECTULUI" 2
Add-Text "Proiectul este organizat în module independente:"
$selection.TypeParagraph()

$modules = @(
    @("BSP", "Definiții hardware specifice pentru Arduino Nano/Uno"),
    @("Drivers", "Straturi de abstracție hardware"),
    @("Logic", "Logica aplicației - control trepte"),
    @("Utils", "Funcții utilitare"),
    @("Test", "Framework de testare pe calculator gazdă"),
    @("Src", "Codul principal al aplicației")
)

foreach ($module in $modules) {
    $selection.Font.Bold = $true
    $selection.TypeText($module[0])
    $selection.Font.Bold = $false
    Add-Text (": " + $module[1])
}
$selection.TypeParagraph()

# Section 4: Drivers
Add-Heading "4. DRIVERE HARDWARE DISPONIBILE" 2
$drivers = @(
    @("GPIO", "Inițializare, citire, scriere, toggle pini"),
    @("Timer0", "Timer sistem cu CTC mode, Millis()"),
    @("Timer1/Timer2", "Timere pentru PWM"),
    @("PWM", "Interfață high-level pentru PWM"),
    @("ADC", "Conversie analog-digitală 10-bit"),
    @("EEPROM", "Citire/scriere memorie persistentă"),
    @("Interrupt", "Suport pentru întreruperi externe"),
    @("USART", "Comunicație serială"),
    @("Switches", "Debouncing și management butoane"),
    @("WS2812", "Control LED-uri RGB adresabile"),
    @("MAX7219", "Control afișaj 7-segmente")
)

foreach ($driver in $drivers) {
    $selection.Font.Bold = $true
    $selection.TypeText($driver[0])
    $selection.Font.Bold = $false
    Add-Text (": " + $driver[1])
}
$selection.TypeParagraph()

# Section 5: Pin Configuration
Add-Heading "5. CONFIGURARE HARDWARE" 2
Add-Text "Pinii Arduino sunt configurați în src/config.h:"
$selection.TypeParagraph()

$pins = @(
    @("WS2812_PIN (Pin 6)", "PORTD.6 - Date LED-uri RGB"),
    @("MAX7219_CS (Pin 10)", "PORTB.2 - Chip Select"),
    @("SPI", "Pini 11-13 (MOSI, MISO, SCK)"),
    @("PADDLE_UPSHIFT (Pin 2)", "PORTD.2 - Urcare trepte"),
    @("PADDLE_DOWNSHIFT (Pin 3)", "PORTD.3 - Coborâre trepte"),
    @("Butoane 12mm", "Pini 4-5"),
    @("Butoane 7mm", "Pini 7-9, A0-A4")
)

foreach ($pin in $pins) {
    $selection.Font.Bold = $true
    $selection.TypeText($pin[0])
    $selection.Font.Bold = $false
    Add-Text (": " + $pin[1])
}
$selection.TypeParagraph()

# Section 6: Data Structures
Add-Heading "6. STRUCTURI DE DATE PRINCIPALE" 2
Add-Text "Tipuri de date definite în src/types.h:"
$selection.TypeParagraph()

$selection.Font.Name = "Courier New"
$selection.Font.Size = 10
$selection.TypeText("typedef enum Gear_t:")
$selection.TypeParagraph()
$selection.TypeText("  GEAR_P, GEAR_R, GEAR_N, GEAR_1...GEAR_8")
$selection.TypeParagraph()
$selection.TypeParagraph()

$selection.TypeText("typedef struct SteeringWheel_State_t:")
$selection.TypeParagraph()
$selection.TypeText("  current_gear, current_speed_kmh")
$selection.TypeParagraph()
$selection.TypeText("  current_rpm, rpm_percentage")
$selection.TypeParagraph()
$selection.TypeText("  upshift_pressed, downshift_pressed")
$selection.TypeParagraph()

$selection.Font.Name = "Calibri"
$selection.Font.Size = 11
$selection.TypeParagraph()

# Section 7: Build System
Add-Heading "7. SISTEMUL DE COMPILARE (MAKEFILE)" 2
Add-Text "Proiectul folosește Makefile pentru compilare și descărcarea firmware-ului."
$selection.TypeParagraph()
$selection.Font.Bold = $true
Add-Text "Comenzi disponibile:"
$selection.Font.Bold = $false

$commands = @(
    @("make all BOARD=nano", "Compilare pentru Arduino Nano"),
    @("make all BOARD=uno", "Compilare pentru Arduino Uno"),
    @("make flash", "Descărcare firmware pe placa conectată"),
    @("make clean", "Ștergere artefacte de compilare"),
    @("make test", "Execută teste unitare"),
    @("make coverage", "Generează raport de acoperire cod")
)

foreach ($cmd in $commands) {
    $selection.Font.Name = "Courier New"
    $selection.TypeText($cmd[0])
    $selection.Font.Name = "Calibri"
    Add-Text (" - " + $cmd[1])
}
$selection.TypeParagraph()

# Section 8: Main Flow
Add-Heading "8. FLUXUL PRINCIPAL (main.c)" 2
Add-Text "1. Inițializare sistem (system_init):"
$selection.TypeParagraph()
$selection.TypeText("   • Inițializare WS2812 LED-uri")
$selection.TypeParagraph()
$selection.TypeText("   • Inițializare MAX7219 afișaj")
$selection.TypeParagraph()
$selection.TypeText("   • Inițializare butoane (switches)")
$selection.TypeParagraph()
$selection.TypeText("   • Inițializare logică control trepte")
$selection.TypeParagraph()
$selection.TypeText("   • Inițializare Timer0")
$selection.TypeParagraph()
$selection.TypeParagraph()

Add-Text "2. Buclă infinită (while 1):"
$selection.TypeParagraph()
$selection.TypeText("   • Actualizare stare butoane (10ms)")
$selection.TypeParagraph()
$selection.TypeText("   • Verificare urcare/coborâre trepte")
$selection.TypeParagraph()
$selection.TypeText("   • Actualizare RPM (20ms)")
$selection.TypeParagraph()
$selection.TypeText("   • Actualizare afișaj 7-segmente")
$selection.TypeParagraph()
$selection.TypeText("   • Actualizare LED-uri RPM")
$selection.TypeParagraph()
$selection.TypeParagraph()

# Section 9: Testing
Add-Heading "9. TESTARE" 2
Add-Text "Proiectul include:"
$selection.TypeParagraph()
Add-Text "• Framework de testare la nivel de calculator gazdă"
Add-Text "• Mock-uri pentru registre AVR"
Add-Text "• Teste unitare pentru GPIO, PWM, și alte componente"
Add-Text "• Generare raport de acoperire cod cu lcov"
$selection.TypeParagraph()

# Section 10: Requirements
Add-Heading "10. CERINȚE DE COMPILARE ȘI DESCĂRCARE" 2
$reqs = @(
    @("avr-gcc", "Compilator GNU pentru AVR"),
    @("avrdude", "Utilitar pentru descărcare firmware"),
    @("make", "Sistem de compilare"),
    @("Arduino Nano/Uno", "Placa de dezvoltare"),
    @("Cablu USB", "Pentru comunicație și alimentare")
)

foreach ($req in $reqs) {
    $selection.Font.Bold = $true
    $selection.TypeText($req[0])
    $selection.Font.Bold = $false
    Add-Text (": " + $req[1])
}
$selection.TypeParagraph()

# Section 11: COM Port Configuration
Add-Heading "11. CONFIGURARE PORT COMUNICAȚIE" 2
Add-Text "În Makefile, configurați portul COM și viteza de transfer:"
$selection.TypeParagraph()

$selection.Font.Name = "Courier New"
$selection.Font.Size = 10
$selection.TypeText("PORT = COM4          # Schimbați în portul conectat")
$selection.TypeParagraph()
$selection.TypeText("BAUD = 57600         # Viteza de transfer")
$selection.TypeParagraph()
$selection.Font.Name = "Calibri"
$selection.Font.Size = 11
$selection.TypeParagraph()

Add-Text "Pentru găsirea portului COM pe Windows, deschideți Device Manager."
$selection.TypeParagraph()

# Section 12: Notes and Best Practices
Add-Heading "12. NOTĂRI ȘI BEST PRACTICES" 2
$notes = @(
    "Proiectul nu folosește bibliotecile Arduino - manipulare directă a registrelor",
    "Fiecare driver este modular și poate fi testat independent",
    "Codul suportă atât Arduino Nano cât și Uno",
    "Debouncing este implementat pentru toate butoanele",
    "Sistemul de timeri asigură precizie de 1ms",
    "LED-urile RGB folosesc protocol WS2812 (NeoPixel)",
    "Afișajul 7-segmente comunică via SPI cu MAX7219",
    "Include suport complet pentru teste unitare și acoperire cod"
)

foreach ($note in $notes) {
    Add-Text "• $note"
}
$selection.TypeParagraph()

# Section 13: Resources
Add-Heading "13. RESURSE" 2
$resources = @(
    @("ATmega328P Datasheet", "https://www.microchip.com/"),
    @("Arduino Nano", "https://www.arduino.cc/en/Guide/ArduinoNano"),
    @("Arduino Uno", "https://www.arduino.cc/en/Guide/ArduinoUno"),
    @("GitHub Proiect", "https://github.com/mamuleanu/embedded-systems-course-atmega328p")
)

foreach ($resource in $resources) {
    $selection.Font.Bold = $true
    $selection.TypeText($resource[0])
    $selection.Font.Bold = $false
    Add-Text (": " + $resource[1])
}

# Save document
$doc.SaveAs($docPath)
Write-Host "Documentația a fost salvată în: $docPath"
Write-Host "Fișier creat cu succes!"
$word.Quit()
