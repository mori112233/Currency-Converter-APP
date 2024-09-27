Currency Converter Application
==============================

Overview
--------

This is a currency conversion application built using C++ with Dear ImGui for 
the graphical user interface (GUI) and httplib for fetching real-time exchange 
rates via API. The application allows users to:

- Select a base currency ("From Currency") and enter an amount.
- Choose a target currency ("To Currency") to display conversion rates.
- View conversion rates for multiple currencies in real time.
- Input an amount and view its equivalent value in other currencies.
- Clear input values using the "Clear" button.

The application fetches live currency conversion rates and displays them in a 
clean, interactive GUI interface. It runs continuously, updating exchange rates 
at regular intervals.


Features
--------

- Live Exchange Rates: Fetches up-to-date exchange rates from the open.er-api.com API.
- User-Friendly Interface: Built using Dear ImGui for a smooth user experience.
- Multiple Currency Support: Allows the user to choose a base currency and display 
  conversion rates for numerous other currencies.
- Conversion Amount Input: Users can enter an amount and see its equivalent in 
  the selected target currency.
- Clear Functionality: A clear button to reset all inputs easily.
- Styled Interface: Customizable colors for the interface, including dark-gray 
  themed input fields and buttons.


Usage
-----

1. **Selecting Currency**:
   
   - Use the "From Currency" dropdown to select the base currency.
   - Enter a target currency in the "To Currency" input box.

2. **Viewing Conversion**:

   - Enter an amount to see its equivalent value in the selected currency.
   - The app will show real-time conversion rates as they are fetched from the API.

3. **Clearing Inputs**:

   - To reset all input fields and start a new conversion, click the "Clear" button.


Code Structure
--------------

- `CommonObject.h`: Defines shared objects and structures like `CurrencyConversion` and 
  `CommonObjects`, which are used for threading and synchronization.
- `DownloadThread.cpp`: Handles the logic for downloading the live exchange rates using 
  the httplib library and parsing them using nlohmann/json.
- `DrawThread.cpp`: Manages the GUI rendering using Dear ImGui. It displays the conversion 
  rates, input fields, and buttons.
- `GuiMain.cpp`: Initializes and manages the window, rendering, and event handling in 
  Dear ImGui.
- `ConnectedApp.cpp`: Coordinates the application’s flow by launching the download thread 
  for fetching exchange rates and the draw thread for rendering the GUI.


API Information
---------------

- Exchange Rates API: https://open.er-api.com/
  
  The app fetches the latest exchange rates from this API using the endpoint `/v6/latest/USD`.


Future Improvements
-------------------

- Customizable Update Intervals: Allow users to set custom intervals for fetching exchange rates.
- Favorite Currencies: Add functionality to mark certain currency pairs as "favorites."
- Graphical Representation: Display historical trends and graphs for selected currency pairs.


Troubleshooting
---------------

- Ensure you have internet connectivity for fetching exchange rates.
- Make sure all dependencies are correctly installed and linked.
- If GUI elements are misaligned, ensure your Dear ImGui settings are properly configured.


License
-------

This project is licensed under the MIT License. See the LICENSE file for more details.


Author
------

Mori Sasson  
LinkedIn: https://www.linkedin.com/in/mori-sason-9a4811281  
Email: 8mori8@gmail.com
