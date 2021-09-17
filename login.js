  1 // pages/openauth/index.js
  2 let App = getApp();
  3 Page({
  4 
  5   /**
  6    * 页面的初始数据
  7    */
  8   data: {
  9     showUserAuth: false //是否显示弹框，默认不显示。
 10   },
 11 
 12   /**
 13    * 生命周期函数--监听页面加载
 14    */
 15   onLoad: function(options) {
 16     //登录小程序
 17     this.WxLogin();
 18   },
 19   /** 登录小程序*/
 20   WxLogin: function() {
 21     let vm = this;
 22     let wxLogin = App.WxLogin();
 23     wxLogin.then((res) => {
 24       //是新用户注册 则 返回 openid 和 session_key 数据
 25       if (res.is_reg) {
 26         //缓存在客户端
 27         wx.setStorageSync('wxInfo', res);
 28         //弹出授权框，让用户授权登录
 29         vm.setData({
 30           showUserAuth: true
 31         });
 32       } else {
 33         //不是新用户注册 则 返回 token 数据
 34         const token = res.token_type + ' ' + res.access_token;
 35         //缓存客户端
 36         wx.setStorageSync('access_token', token);
 37         //跳转至首页（tabbar）
 38         // App.GetLoacationOrGoHome();
 39         //检查是否需要重新授权
 40         wx.getSetting({
 41           success(res) {
 42             if (res.authSetting["scope.userInfo"]) {
 43               console.log("正在获取老用户最新的用户信息");
 44               wx.getUserInfo({
 45                 success: function(res) {
 46                   //缓存最新用户信息
 47                   App.globalData.userInfoBool = true; //以获取到地理位置
 48                   wx.setStorageSync('userInfo', res.userInfo);
 49                   console.log("正在缓存用户信息，跳转至 首页....");//准备前往获取地理位置
 50                   //跳转至首页（tabbar）
 51                   App.GetLoacationOrGoHome();
 52                 }
 53               });
 54              
 55             } else {
 56               console.log("检测到老用户未授权（清除了授权数据），需要重新授权...");
 57               //需要重新授权
 58               App.globalData.needReauth =true;
 59               //打开授权弹窗
 60               vm.setData({
 61                 showUserAuth: true
 62               });
 63             }
 64           }
 65         })
 66   
 67       }
 68     }).catch((msg) => {
 69       console.error('小程序登录错误(login)：' + msg);
 70     });
 71   },
 72   /** 用户点击 授权登录*/
 73   GetUserInfo: function(e) {
 74     let vm = this;
 75     //缓存 用户信息数据 
 76     if (e.detail.errMsg =="getUserInfo:fail auth deny"){
 77       console.log("用户拒绝授权用户信息，再次尝试让用户同意！");
 78       wx.showModal({
 79         content: '你需要【授权登录】并允许 motiva 获取你的微信头像、昵称等信息，请点击确定继续。',
 80         success(res) {
 81           if (!res.confirm) {
 82             // vm.ChooseLocation()
 83           }
 84         }
 85       })
 86     }else{
 87       console.log("已同意授权，正在缓存用户信息");
 88       App.globalData.userInfo = e.detail.userInfo;
 89       wx.setStorageSync('userInfo', userInfo);
 90       if (App.globalData.needReauth) {//老用户 重新授权
 91         console.log("老用户就走到这里，跳转至 首页....");//准备前往获取地理位置
 92         App.GetLoacationOrGoHome();
 93         return
 94       }
 95       console.log("新用户开始注册...");
 96       //格式化数据：取出缓存中 session_key 和 openid  与 用户数据
 97       let wxInfo = wx.getStorageSync('wxInfo');
 98       e.detail.openid = wxInfo.openid;
 99       e.detail.session_key = wxInfo.session_key;
100       let info = JSON.stringify(e.detail);
101       //发送 保存数据库的 请求
102       let userInfo = App.SaveUserInfo(info);
103       userInfo.then((res) => {
104         console.log("新用户注册成功");
105         //请求成功 后返回 token 数据
106         const token = res.token_type + ' ' + res.access_token;
107         //缓存token 数据
108         wx.setStorageSync('access_token', token);
109         console.log("缓存用户信息，跳转至 首页....");//准备前往获取地理位置
110         //跳转至首页（tabbar）
111         App.GetLoacationOrGoHome();
112       }).catch(msg => {
113         console.error("保存用户数据失败(registered)：" + msg);
114         this.setData({
115           showUserAuth: true
116         });
117       });
118     }
119   }
120 })  1 // pages/openauth/index.js

  2 let App = getApp();
  3 Page({
  4 
  5   /**
  6    * 页面的初始数据
  7    */
  8   data: {
  9     showUserAuth: false //是否显示弹框，默认不显示。
 10   },
 11 
 12   /**
 13    * 生命周期函数--监听页面加载
 14    */
 15   onLoad: function(options) {
 16     //登录小程序
 17     this.WxLogin();
 18   },
 19   /** 登录小程序*/
 20   WxLogin: function() {
 21     let vm = this;
 22     let wxLogin = App.WxLogin();
 23     wxLogin.then((res) => {
 24       //是新用户注册 则 返回 openid 和 session_key 数据
 25       if (res.is_reg) {
 26         //缓存在客户端
 27         wx.setStorageSync('wxInfo', res);
 28         //弹出授权框，让用户授权登录
 29         vm.setData({
 30           showUserAuth: true
 31         });
 32       } else {
 33         //不是新用户注册 则 返回 token 数据
 34         const token = res.token_type + ' ' + res.access_token;
 35         //缓存客户端
 36         wx.setStorageSync('access_token', token);
 37         //跳转至首页（tabbar）
 38         // App.GetLoacationOrGoHome();
 39         //检查是否需要重新授权
 40         wx.getSetting({
 41           success(res) {
 42             if (res.authSetting["scope.userInfo"]) {
 43               console.log("正在获取老用户最新的用户信息");
 44               wx.getUserInfo({
 45                 success: function(res) {
 46                   //缓存最新用户信息
 47                   App.globalData.userInfoBool = true; //以获取到地理位置
 48                   wx.setStorageSync('userInfo', res.userInfo);
 49                   console.log("正在缓存用户信息，跳转至 首页....");//准备前往获取地理位置
 50                   //跳转至首页（tabbar）
 51                   App.GetLoacationOrGoHome();
 52                 }
 53               });
 54              
 55             } else {
 56               console.log("检测到老用户未授权（清除了授权数据），需要重新授权...");
 57               //需要重新授权
 58               App.globalData.needReauth =true;
 59               //打开授权弹窗
 60               vm.setData({
 61                 showUserAuth: true
 62               });
 63             }
 64           }
 65         })
 66   
 67       }
 68     }).catch((msg) => {
 69       console.error('小程序登录错误(login)：' + msg);
 70     });
 71   },
 72   /** 用户点击 授权登录*/
 73   GetUserInfo: function(e) {
 74     let vm = this;
 75     //缓存 用户信息数据 
 76     if (e.detail.errMsg =="getUserInfo:fail auth deny"){
 77       console.log("用户拒绝授权用户信息，再次尝试让用户同意！");
 78       wx.showModal({
 79         content: '你需要【授权登录】并允许 motiva 获取你的微信头像、昵称等信息，请点击确定继续。',
 80         success(res) {
 81           if (!res.confirm) {
 82             // vm.ChooseLocation()
 83           }
 84         }
 85       })
 86     }else{
 87       console.log("已同意授权，正在缓存用户信息");
 88       App.globalData.userInfo = e.detail.userInfo;
 89       wx.setStorageSync('userInfo', userInfo);
 90       if (App.globalData.needReauth) {//老用户 重新授权
 91         console.log("老用户就走到这里，跳转至 首页....");//准备前往获取地理位置
 92         App.GetLoacationOrGoHome();
 93         return
 94       }
 95       console.log("新用户开始注册...");
 96       //格式化数据：取出缓存中 session_key 和 openid  与 用户数据
 97       let wxInfo = wx.getStorageSync('wxInfo');
 98       e.detail.openid = wxInfo.openid;
 99       e.detail.session_key = wxInfo.session_key;
100       let info = JSON.stringify(e.detail);
101       //发送 保存数据库的 请求
102       let userInfo = App.SaveUserInfo(info);
103       userInfo.then((res) => {
104         console.log("新用户注册成功");
105         //请求成功 后返回 token 数据
106         const token = res.token_type + ' ' + res.access_token;
107         //缓存token 数据
108         wx.setStorageSync('access_token', token);
109         console.log("缓存用户信息，跳转至 首页....");//准备前往获取地理位置
110         //跳转至首页（tabbar）
111         App.GetLoacationOrGoHome();
112       }).catch(msg => {
113         console.error("保存用户数据失败(registered)：" + msg);
114         this.setData({
115           showUserAuth: true
116         });
117       });
118     }
119   }
120 })
