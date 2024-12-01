// import { echarts } from '../../ec-canvas/echarts.js'
 
App({
  globalData:{
    temp: 0,
    humi: 0,
    light: 0,
    air: 0,
    water: 0,
    rain: 0,
    one: 0,
    atmos: 0,
    ph: 0,
    xph: 0,
    tds: 0,
    waterhight: 0,
    orp: 0,
    light: 0,
    watertemp: 0,
    isOn: 0,
    feeding: 0,
    o2: 0,
  }
});
Page({
  onShareAppMessage: function (res) {
    return {
      title: 'ECharts 可以在微信小程序中使用啦！',
      path: '/pages/index/index',
      success: function () {},
      fail: function () {}
    }
  },
 
  onReady() {
},
  // 事件处理函数
  getinfo(){
    var that = this
    wx.request({
    url: "https://api.heclouds.com/devices/1202725242/datapoints",   
    //将请求行中的数字换成自己的设备ID
    header: {
      "api-key": "YJ=3hqMFW4oW1=ibQWOgR0NSEGY=" //自己的api-key
    },
    method: "GET",
    success: function (e) {

      console.log("获取成功",e)
      that.setData({
          temp:e.data.data.datastreams[2].datapoints[0].value,//temp
          humi:e.data.data.datastreams[11].datapoints[0].value,//humi
          light:e.data.data.datastreams[5].datapoints[0].value ,//lux
          tds:e.data.data.datastreams[13].datapoints[0].value,//fire
          orp:e.data.data.datastreams[1].datapoints[0].value,//rain
         
          waterhight:e.data.data.datastreams[4].datapoints[0].value,//alt
          atmos:e.data.data.datastreams[7].datapoints[0].value,//atmos
          watertemp:e.data.data.datastreams[3].datapoints[0].value,//co2
          ph:e.data.data.datastreams[0].datapoints[0].value, //tvoc         
          feeding:e.data.data.datastreams[9].datapoints[0].value,//feeding
          

      })
      console.log("temp==",that.data.temp)
    }
   });
  }, 
  kai:function(){  
    let data={
      "datastreams": [  
        
    {"id": "ledbtn","datapoints":[{"value":1}]},
    //led是数据流的名称，value是要传上去的数值
        ]	
    }
   //按钮发送命令控制硬件
    wx.request({
      url:'https://api.heclouds.com/devices/1202725242/datapoints',//设备号
      header: {
        'content-type': 'application/json',
        'api-key':'YJ=3hqMFW4oW1=ibQWOgR0NSEGY='//密匙
      },
      method: 'POST',
      data: JSON.stringify(data),//data数据转换成JSON格式
      success(res){
        console.log("成功",res.data)
      },
      fail(res){
        console.log("失败",res)
      }
    })
    this.setData({
      isOn: 1 // 修改 isOn 变量的值为 true，表示开机状态
    });
  },  
 kaic:function(){
  let data={
    "datastreams": [  
  {"id": "feeding","datapoints":[{"value":1}]},
  //led是数据流的名称，value是要传上去的数值
      ]	
  }
 //按钮发送命令控制硬件
  wx.request({
    url:'https://api.heclouds.com/devices/1202725242/datapoints',//设备号
    header: {
      'content-type': 'application/json',
      'api-key':'YJ=3hqMFW4oW1=ibQWOgR0NSEGY='//密匙
    },
    method: 'POST',
    data: JSON.stringify(data),//data数据转换成JSON格式
    success(res){
      console.log("成功",res.data)
    },
    fail(res){
      console.log("失败",res)
    }
  })
  this.setData({
    feeding: 1 // 修改 isOn 变量的值为 true，表示开机状态
  });
},  
 guan:function(){
  let data={
   "datastreams": [  
 {"id": "ledbtn","datapoints":[{"value": 0}]},
 //led是数据流的名称，value是要传上去的数值
     ]	
 }
  //按钮发送命令控制硬件
   wx.request({
     url:'https://api.heclouds.com/devices/1202725242/datapoints',//
     header: {
       'content-type': 'application/json',
       'api-key':'YJ=3hqMFW4oW1=ibQWOgR0NSEGY='
     },
     method: 'POST',
     data: JSON.stringify(data),//data数据转换成JSON格式
     success(res){
       console.log("成功",res.data)
     },
     fail(res){
       console.log("失败",res)
     }
   })
   this.setData({
    isOn: 0 // 修改 isOn 变量的值为 true，表示开机状态
  });
},  
guanc:function(){
  isOn:1
  let data={
   "datastreams": [  
 {"id": "feeding","datapoints":[{"value": 0}]},
 //led是数据流的名称，value是要传上去的数值
     ]	
 }
  //按钮发送命令控制硬件
   wx.request({
     url:'https://api.heclouds.com/devices/1202725242/datapoints',//
     header: {
       'content-type': 'application/json',
       'api-key':'YJ=3hqMFW4oW1=ibQWOgR0NSEGY='
     },
     method: 'POST',
     data: JSON.stringify(data),//data数据转换成JSON格式
     success(res){
       console.log("成功",res.data)
     },
     fail(res){
       console.log("失败",res)
     }
   })
   this.setData({
    feeding: 0 // 修改 isOn 变量的值为 true，表示开机状态
  });
},   


viewTempData: function(e) {
  console.log("AAA成功",e)
  wx.navigateTo({
    url: '../' +'tempp' + '/tempp'
  })
},
viewHumiData: function(e) {
  wx.navigateTo({
    url: '../' +'humi' + '/humi'
  })
},
viewLightData: function(e) {
  wx.navigateTo({
    url: '../' +'light' + '/index'
  })
},
viewAtmosData: function(e) {
  wx.navigateTo({
    url: '../' +'atmos' + '/atmos'
  })
},
viewwaterhightData: function(e) {
  wx.navigateTo({
    url: '../' +'waterhight' + '/waterhight'
  })
},
viewwatertempData: function(e) {
  wx.navigateTo({
    url: '../' +'watertemp' + '/watertemp'
  })
},
viewphData: function(e) {
  wx.navigateTo({
    url: '../' +'ph' + '/ph'
  })
},
viewtdsData: function(e) {
  wx.navigateTo({
    url: '../' +'tds' + '/tds'
  })
},
vieworpData: function(e) {
  wx.navigateTo({
    url: '../' +'orp' + '/orp'
  })
},
  onLoad() {
    var that = this
    setInterval(function()
    {
      that.getinfo()
    },1000)//3000ms刷新一次

    
  }
})
