## 目录
* <a href="#Intro">1.引言</a>
    * <a href="#purpose">1.1 编写目的</a>
    * <a href="#brief_intro">1.2 项目简介</a>
    * <a href="#refer">1.3 参考资料</a>
* <a href="#total_intro">2.总体描述</a>
    * <a href="#background">2.1 项目背景</a>
    * <a href="#purpose1">2.2 项目目标</a>
    * <a href="#user_case">2.3 典型用户场景</a>
    * <a href="#user_require">2.4 典型用户需求说明</a>
    * <a href="#env">2.5 运行环境要求</a>
* <a href="#pre_assu">3. 前提与假设</a>
* <a href="#page">4. 页面原型设计</a>
* <a href="#standard">5. 系统功能描述验收标准</a>
    * <a href="function_rule">5.1 对功能的规定</a>
    
### <a name="Intro" id="Intro">1. 引言</a>
#### <a name="purpose" id="purpose">1.1 编写目的</a>
此需求规格说明书编制目的是明确本项目的详细需求，确认项目的功能和性能，和用户形成一致的理解和确认，作为进一步详细设计软件的基础。本文档仅供本项目全体成员，包括项目经理、设计人员、开发人员参考。

#### <a name="brief_intro" id="brief_intro">1.2 项目简介</a>
- 项目名称： 拼团旅游网站
- 项目面向用户：个人博主
- 项目开发者：武汉大学软工实践 C++team小组

#### <a name="refer" id="refer">1.3 参考资料</a>
- 各种博客资料
- 《构建之法》(第二版)，邹欣。

### <a name="total_intro" id="total_intro">2. 总体描述</a>
  #### <a name="background" id="background">2.1 项目背景</a>
  通过调查，目前还没有出现拼团旅游的网站。特别是现在适合年轻人自己规划路线，自己寻找旅友的独立平台。有些人想和其他人一起游玩，但是又不想在外面报旅游团，目前只能在贴吧、微信群、QQ群发布自己的消息，寻求伙伴，我们这个网站，就是集合一群准备旅游的人，能够让用户在有旅游打算时，能够输入自己信息，立马找到有相同行程的人，根据这些来自主选择同行伙伴。让旅途不再孤单，让旅途更加自由。
  #### 2.2 项目目标
  完成网站的基本功能，主要包括登录、注册、个人信息修改、轨迹搜索、同行者信息反馈。对于游客来说，可以进行搜索路线、浏览功能。
  
  #### <a name="user_case" id="user_case">2.3 典型用户场景</a>
#####   我们的系统主要面向两类用户：      
  - 用户
  - 普通游客
 
  1. 大学生花生

<table border="0" cellpadding="0" cellspacing="0" id="sheet0" class="sheet0 gridlines">
		<col class="col0">
		<col class="col1">
		<tbody>
		  <tr class="row0">
			<td class="column0 style1 s">姓名 </td>
			<td class="column1 style1 s">花生</td>
		  </tr>
		  <tr class="row1">
			<td class="column0 style1 s">性别</td>
			<td class="column1 style1 s">女</td>
		  </tr>
		  <tr class="row2">
			<td class="column0 style1 s">职业</td>
			<td class="column1 style1 s">武汉大学研究生在读</td>
		  </tr>
		  <tr class="row3">
			<td class="column0 style1 s">知识层次和能力</td>
			<td class="column1 style1 s">研究生，生活各个方面都会使用电脑，有一定经济条件</td>
		  </tr>
		  <tr class="row4">
			<td class="column0 style1 s">动机、目的、困难</td>
			<td class="column1 style1 s">动机、目的：享受旅游快感，扩大交友面。困难：没有时间自己去专门寻找同行伙伴</td>
		  </tr>
		  <tr class="row5">
			<td class="column0 style1 s">用户偏好</td>
			<td class="column1 style1 s">都是大学生，学历思想大概相同</td>
		  </tr>
		  <tr class="row6">
			<td class="column0 style1 s">用户比例</td>
			<td class="column1 style1 s">40%</td>
		  </tr>
		  <tr class="row7">
			<td class="column0 style1 s">典型场景</td>
			<td class="column1 style1 s">在网站上登记自己个人信息，将自己始发地与目的地，以及出发时间发布，寻找同行的人，筛选出自己满意的同行者</td>
		  </tr>
		  <tr class="row8">
			<td class="column0 style1 s">典型描述</td>
			<td class="column1 style1 s">找自己满意的线路，交满意的朋友</td>
		  </tr>
		</tbody>
	</table>

  2.某公司职员追梦
    
<table border="0" cellpadding="0" cellspacing="0" id="sheet0" class="sheet0 gridlines">
		<col class="col0">
		<col class="col1">
		<tbody>
		  <tr class="row0">
			<td class="column0 style1 s">&nbsp;姓名</td>
			<td class="column1 style2 s">追梦</td>
		  </tr>
		  <tr class="row1">
			<td class="column0 style1 s">&nbsp;性别</td>
			<td class="column1 style2 s">男</td>
		  </tr>
		  <tr class="row2">
			<td class="column0 style1 s">&nbsp;职业</td>
			<td class="column1 style2 s">IT工程师</td>
		  </tr>
		  <tr class="row3">
			<td class="column0 style1 s">&nbsp;知识层次和能力</td>
			<td class="column1 style2 s">大学，热爱旅游，有经济实力</td>
		  </tr>
		  <tr class="row4">
			<td class="column0 style1 s">&nbsp;动机、目的、困难</td>
			<td class="column1 style2 s">动机、目的：享受旅游，带着家人自主旅游，想让孩子见到更多风景和人。困难：不容易找到一起同行的其他家庭，或者找到和满意的同行者</td>
		  </tr>
		  <tr class="row5">
			<td class="column0 style1 s">&nbsp;用户偏好</td>
			<td class="column1 style2 s">旅行、交友、开阔眼界、培养孩子</td>
		  </tr>
		  <tr class="row6">
			<td class="column0 style1 s">&nbsp;用户比例</td>
			<td class="column1 style3 n">40%</td>
		  </tr>
		  <tr class="row7">
			<td class="column0 style4 s">&nbsp;典型场景</td>
			<td class="column1 style2 s">提交行程信息，得到反馈，寻找自己满意的同行者</td>
		  </tr>
		</tbody>
	</table>
  
  3.学生颗粒（游客）
    
<table border="0" cellpadding="0" cellspacing="0" id="sheet0" class="sheet0 gridlines">
		<col class="col0">
		<col class="col1">
		<tbody>
		  <tr class="row0">
			<td class="column0 style1 s">&nbsp;姓名</td>
			<td class="column1 style2 s">颗粒</td>
		  </tr>
		  <tr class="row1">
			<td class="column0 style1 s">&nbsp;性别</td>
			<td class="column1 style2 s">男</td>
		  </tr>
		  <tr class="row2">
			<td class="column0 style1 s">&nbsp;职业</td>
			<td class="column1 style2 s">武汉大学大学生</td>
		  </tr>
		  <tr class="row3">
			<td class="column0 style1 s">&nbsp;知识层次和能力</td>
			<td class="column1 style2 s">大学，喜欢找网上的旅游线路分享，但是懒得走出去，只是看一下世界大好河川</td>
		  </tr>
		  <tr class="row4">
			<td class="column0 style1 s">&nbsp;动机、目的、困难</td>
			<td class="column1 style2 s">动机、目的：看看美景，了解一下有哪些好玩地方和路线，以后有机会再走出去。困难：不想行动</td>
		  </tr>
		  <tr class="row5">
			<td class="column0 style1 s">&nbsp;用户偏好</td>
			<td class="column1 style2 s">旅行信息收集、开阔眼界</td>
		  </tr>
		  <tr class="row6">
			<td class="column0 style1 s">&nbsp;用户比例</td>
			<td class="column1 style3 n">20%</td>
		  </tr>
		  <tr class="row7">
			<td class="column0 style4 s">&nbsp;典型场景</td>
			<td class="column1 style2 s">搜索目的地与始发地，查看推荐路线</td>
		  </tr>
		</tbody>
	</table>
    
  #### <a name="user_require" id="user_require">2.4 典型用户需求说明</a>
  1. 花生和追梦：注册成为网站会员，登陆自己账户，输入始发地，目的地和始发时间，查找到合适路线与同行人信息；并且可以对自己信息进行编辑修改，已经自己账户的注销。
  2. 颗粒：能够搜索、浏览网站。
 
  #### <a name="env" id="env">2.5 运行环境要求</a>
##### <a name="" id="">1.服务器</a>
##### 平台
可在各个系统运行（Windows、Linux等）。
##### <a name="" id="">2.浏览器</a>
通过使用 HTML5 提供的 API，以及 CSS3 提供的新样式，可支持所有现代浏览器

| 浏览器   | Chrome | Edge | Firefox | Internet Explorer | Opera | Safari |
| -------- | ------ | ---- | ------- | ----------------- | ----- | ------ |
| 最低版本 | 5      | All  | 4.0     | 10                | 11.50 | 5.0    |

### <a name="pre_assu" id="pre_assu">3.前提与假设</a>
##### <a name="" id="">前提</a>       
1.技术前提：小组成员都熟悉C++语言，有一定的编程经验，熟练运用VS、QT软件。  
2.人员前提：小组成员积极合作，每次会议能有效开展，都能完成阶段性任务，小组主要成员基本不会出现变动，并且在项目开发过程中不会因为突发情况的发生而导致项目成员无法正常参与开发工作。  
3.需求限定：假设项目需求基本确定之后，不会有太大改变。
##### 假设
1. 可操作性：假定用户在经过一段时间熟悉之后，可以灵活地操作本网站来满足自己的需要。    
2. 用户支持：假定在本网站在开发的各个环节中得到用户的有效支持和配合。    
3. 时间限定：假定项目的截止时间不会提前。    
4. 需求限定：假定项目需求基本确定之后，不会有太大改变。

### <a name="page" id="page">4.主要界面原型设计</a>
主要界面：用户注册、登录、主界面、修改个人信息页面、注销页面
#后续补充......

### <a name="standard" id="standard">5.系统功能描述验收标准</a>
5.1 用户登录/注册页面
 1.注册按钮：能跳转到登录页面；  
 2.登录：当输入正确的用户名、密码和验证码能跳转到主页；  
        输入错误的用户名或者密码，有相对应的提示信息，且对用户输入信息进行检查与过滤，防止SQL注入等；  
5.2 注册页面
  用户信息的输入，输入框有提示，且二次输入密码时，前端有验证，点击提交按钮，有
5.3 主页
 1.输入：始发地、
