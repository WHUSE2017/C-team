# 20171025
## 完成情况
1. 美化UI设计，如字体、按钮样式、背景等
2. 登录界面中的验证码实现。
3. 程序中变量文档的编写

## 遇到的问题
1. QLabel的点击事件的实现

## 下一步计划
1. 解决问题
2. 优化UI设计

# 20171026
## 完成情况
1. 完善界面的设计，完善各个按钮的点击事件
2. 优化UI设计
3. 改变字体样式

## 遇到的问题
1. 窗体之间的切换问题
2. 整个软件的全局变量设置

## 下一步计划
1. 解决问题
2. 在程序文件添加更加详细的注释

# 20171027
## 完成情况
1. 美化了界面中按钮、输入框和字体样式
2. 增加了换皮肤功能
3. 规范化了程序中的变量和函数命名方式
4. 进一步完善了UI中点击事件

## 遇到的问题
1. 字体切换问题，想要的字体文件加载不了
2. 图片的处理问题

## 下一步计划
1. 解决问题
2. 完善UI设计文档的编写
3. 在皮肤中美化UI界面


# 20171029
# 完成情况
- 前端和后端整合
- 登录正常，站内信息正常，个人信息查看正常，搜索正常，详情正常

# 问题
- 注册不能输入中文，数据库中手机号和学号类型问题
- 不能发布组团信息
- 不能搜索所有组团信息

# 下一步计划
- 密码加密存储，实现记住密码
- 解决问题
- 加入组团信息到数据库


关于中文可能出现问题的解决方案：
进行url编码

1.QString先进行url编码，然后转换为stdstring，赋值给相应的结构体，这样就能保证整个传输过程中不会出现中文。

2.查询获取数据是：获取到stdstring，转化为QString ,然后对QString进行url解码，显示到界面。

因为现在无法在去改代码来处理中文了，就只能用这种方式来解决中文问题了。。。



std::stoi(

有趣初始化的顺序就是光标走的顺序
trimmed()
tr()
string.data()

http://www.aiuxian.com/article/p-1650536.html
http://www.aiuxian.com/article/p-1476312.html
http://www.cnblogs.com/onlycxue/archive/2012/10/30/2746902.html
http://blog.chinaunix.net/uid-26696487-id-3134286.html
http://blog.csdn.net/zuoyuexian/article/details/74550345
http://blog.csdn.net/qq_33227451/article/details/52221237
https://www.douban.com/note/273400388/
403错误


