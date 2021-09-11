# Stock Chart and Plotting Tool
**Stock Chart** is a simple stock visualization framework developed under Linux environment with CMake and Qt. The tool has been tested for both Linux and Windows.

<img src="../main/images/22.png?raw=true" height="600">
<img src="../main/images/23.png?raw=true" height="600">

## This project supports the following functions:
* Python: 
  * Download stock history data from Yahoo Finance as CSV file.
  * Calculate and save stock prices and indicators as CSV file including:
    * Prices: Open, High, Low, Close, Adj Close
    * Volume
    * Moving Average (MA): 5, 10, 20, 30, 60, 120 days
    * Exponential Moving Average (EMA): 5, 10, 20, 30, 60, 120 days
    * Moving Average Convergence Divergence (MACD)
    * BOLLinger bands (BOLL)
	* KDJ
    * Relative Strength Index (RSI)
* C++:
  * Load CSV file into Plot and Chart windows
  * Interactive visualizations of different stock prices and indicators in Plot window

## Prerequisite
* Python: pandas, [stock_pandas](https://github.com/kaelzhang/stock-pandas), datetime, yfinance
* C++: Qt

## Part 1 - Python
1. Run ExportCSV_Python/exportcsv.py to download stock history data with stock symbol, interval, and time range, e.g. Save 1-day "SPX" data between "13/30/1927" and "12/4/2020" to "spx.csv" file.
Note that, the stock history data can also be downloaded directly from Yahoo Finance website.
2. Run ExportCSV_Python/readcsv2.py to calculate and save stock and indicators as CSV file, e.g. Save 1-day "SPX" price and indicators to "spxMetric.csv"
<img src="../main/images/11.png?raw=true" height="400">

## Part 2 - C++
1. Run C++ GUI to invoke the Stock Chart and Plotting Tool
<img src="../main/images/1.png?raw=true" height="400">
<img src="../main/images/2.png?raw=true" height="400">

2. Under "File" Menu, click "Open .CSV File" and load the "spxMetric.csv" we saved from Python
<img src="../main/images/3.png?raw=true" height="200">

The tool can then read stock data into the "Stock Plot" and "Stock Table" tabs
<img src="../main/images/12.png?raw=true" height="400">
<img src="../main/images/13.png?raw=true" height="400">
<img src="../main/images/14.png?raw=true" height="400">

3. Under the "Stock Indicators" menu, the user can show/hide different stock indicators in the Plot window.
<img src="../main/images/4.png?raw=true" height="200"> <img src="../main/images/5.png?raw=true" height="200">
<img src="../main/images/6.png?raw=true" height="200"> <img src="../main/images/7.png?raw=true" height="200">
<img src="../main/images/8.png?raw=true" height="200"> <img src="../main/images/9.png?raw=true" height="200">
  <img src="../main/images/10.png?raw=true" height="200"> 

4. The user can also use mouse wheel and buttons to zoom in and out for a specific date period. The user can also use different combinations of indicators to analyze a stock/index's trend. A few examples below:
<img src="../main/images/15.png?raw=true" height="400">
<img src="../main/images/16.png?raw=true" height="400">
<img src="../main/images/17.png?raw=true" height="400">
<img src="../main/images/18.png?raw=true" height="400">
<img src="../main/images/19.png?raw=true" height="400">
<img src="../main/images/20.png?raw=true" height="400">
<img src="../main/images/21.png?raw=true" height="400">