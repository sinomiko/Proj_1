# 计算（MA）均线
# 方法一：最原始的手工计算，只用到了DataFrame，通过mean方法逐行计算多日平均数。

import numpy as np
import pandas as pd
from pandas import Series, DataFrame

# 获得上证指数日行情
df = DataAPI.MktIdxdGet(tradeDate=u"",indexID=u"",ticker=u"000001",beginDate=u"20140101",endDate=u"20160717",field=u"tradeDate,closeIndex",pandas="1")
# 添加5、10、20、60日均线值列，只取出收盘价（新建一个只有收盘价的DataFrame计算速度快很多）
dd = DataFrame(df, columns=['closeIndex','MA5','MA10','MA20','MA60'])

# Moving Average
i = 0
count = len(dd)
while i <= count:
    if i >= 5:
        dd['MA5'][i-1] = dd['closeIndex'][i-5:i].mean()
    if i >= 10:
        dd['MA10'][i-1] = dd['closeIndex'][i-10:i].mean()
    if i >= 20:
        dd['MA20'][i-1] = dd['closeIndex'][i-20:i].mean()
    if i >= 60:
        dd['MA60'][i-1] = dd['closeIndex'][i-60:i].mean()
    i += 1

# 合并两个DataFrame
df = pd.merge(df,dd,how='outer')

# 绘图
df = df.set_index('tradeDate')
df.plot(y=['MA5','MA10','MA20','MA60'],figsize=(16,9),title='20140101-20160717 MA')