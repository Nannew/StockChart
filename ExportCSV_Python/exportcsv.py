import yfinance as yf

# Download stock data then export as CSV

#data_df = yf.download("SPY", interval="1h", start="2020-01-01", end="2021-09-09", prepost="True")
#data_df.to_csv('spy1.csv')


# spx data can also be downloaded directly from yahoo finance website
data_df = yf.download("SPX", interval="1d", start="1927-12-30", end="2021-09-09", prepost="True")
data_df.to_csv('spx.csv')