# Analog to Digital Converter:

###  How to use ADC full power:

* Set the ADC clock prescaler (default: disabled, which means no conversions) [**MUST !!**]
* Set the voltage reference that defines the full scale (default: an externally supplied
voltage) [**MUST !!**]
* Set the analog channel to sample from (default: external pin PC0) [**MUST !!**]
* Set an ADC trigger source (default: free-running if specified)
* Set interrupts to call when an ADC conversion is complete (default: none)
* Set other miscellaneous options including an 8-bit mode, turning off the digital
input circuitry to save power, and more
