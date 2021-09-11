# Ref: https://github.com/kaelzhang/stock-pandas

import stock_pandas as spd
import pandas as pd
import datetime

pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)



def parser(x):
    return datetime.datetime.strptime(x,'%Y-%m-%d')


stock = spd.StockDataFrame(pd.read_csv('spx.csv', header=0, parse_dates=[0], date_parser=parser))

# print(stock.get_column('Close').head(5))

stock.alias('date', 'Date')
stock.alias('open', 'Open')
stock.alias('high', 'High')
stock.alias('low', 'Low')
stock.alias('adj close', 'Adj Close')
stock.alias('close', 'Close')
stock.alias('volume', 'Volume')

# print(stock['ma:2'].head(5))


# Dataframe of 5-period, 10-period, 30-period ma
stock[[
    'ma:5',
    'ma:10',
    'ma:20',
    'ma:30',
    'ma:60',
    'ma:120',
]]

# Exponential Moving Average
stock[[
    'ema:5',
    'ema:10',
    'ema:20',
    'ema:30',
    'ema:60',
    'ema:120',
]]

# macd
stock['macd']
stock['macd.dif']
stock['macd.signal']
stock['macd.dea']

# boll
stock['boll']

# bollinger upper band, a shortcut for stock['boll.upper']
# stock['boll.u']
stock['boll.upper']

# bollinger lower band, which is equivalent to stock['boll.l']
stock['boll.lower']
# stock['boll.l']


# The KDJ serieses of with parameters 9, 3, and 3
stock[['kdj.k:9,3', 'kdj.d:9,3', 'kdj.j:9,3,3']]

# RSI
stock[[
    'rsi:6',
    'rsi:12',
    'rsi:24'
]]


print(stock.head(20))

stock.to_csv('spxMetric.csv')