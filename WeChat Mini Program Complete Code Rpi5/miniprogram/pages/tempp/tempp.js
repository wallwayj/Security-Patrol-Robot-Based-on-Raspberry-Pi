import * as echarts from '../../ec-canvas/echarts';


const app = getApp();

let xAxisArray = new Array();//横坐标
let yAxisArray = new Array();//纵坐标
let timer;//定时刷新，页面退出后关闭定时器


// 曲线设置
function setOption(chart, xdata, ydata) {
  const option = {
    title: {
      text: '实时温度显示',
      left: 'center',
      textStyle: {
        color: '#333',
        fontWeight: 'bold',
        fontSize: 20
      }
    },
    grid: {
      top: '15%',
      left: '5%',
      right: '5%',
      bottom: '5%',
      containLabel: true
    },
    tooltip: {
      trigger: 'axis'
    },
    xAxis: {
      type: 'category',
      boundaryGap: false,
      data: xdata,
      axisLine: {
        lineStyle: {
          color: '#999999'
        }
      },
      axisLabel: {
        color: '#666666',
        interval: 0, // 设置x轴刻度标签全部显示
        rotate: 45 // 旋转角度，适应更长的时间刻度
      }
    },
    yAxis: {
      type: 'value',
      splitLine: {
        lineStyle: {
          type: 'dashed',
          color: '#CCCCCC'
        }
      },
      axisLine: {
        lineStyle: {
          color: '#999999'
        }
      },
      axisLabel: {
        color: '#666666',
        formatter: '{value}℃' // 设置y轴刻度值的格式为温度单位（℃）
      }
    },
    series: [{
      name: '温度',
      type: 'line',
      smooth: true,
      symbol: 'circle',
      symbolSize: 8,
      lineStyle: {
        color: '#00BFFF',
        width: 2
      },
      itemStyle: {
        color: '#00BFFF'
      },
      data: ydata
    }]
  };
  chart.setOption(option);
}

Page({
  data: {

    ec: {
      lazyLoad: true
    },
  },
  /**
   * 生命周期函数--监听页面加载
   */
  
  onLoad(options) {
    // 初始化曲线
    this.init_echart();
  
    let count = 0;
    // 每隔1秒刷新前7次
    timer = setInterval(() => {
      count++;
      this.getOption();
      if (count >= 7) {
        clearInterval(timer);
        // 每隔1000秒刷新之后的数据
        timer = setInterval(() => {
          this.getOption();
        }, 5000);
      }
    }, 1000);
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {
    clearInterval(timer)//注销定时器
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  // 初始化图表，放在 onLoad() 中(主要是为了得到 myChart )
  init_echart: function () {
    this.Component = this.selectComponent('#mychart-temp');
    this.Component.init((canvas, width, height) => {
      const chart = echarts.init(canvas, null, {
        width: width,
        height: height
      });
      this.myChart = chart;//这里直接将初始化的图标传递到参数 myChart 中
      return chart;
    })
  },
  // 给图表加上数据
  getOption: function () {
    var currentTime = new Date();
    var cc = convertTime(currentTime); // 将日期转换为时分秒形式
  
    var that = this;
    wx.request({
      url: "https://api.heclouds.com/devices/1078668849/datapoints",
      //将请求行中的数字换成自己的设备ID
      header: {
        "api-key": "YJ=3hqMFW4oW1=ibQWOgR0NSEGY=" //自己的api-key
      },
      method: "GET",
      success: function (e) {
        console.log("获取成功", e);
        var ra = e.data.data.datastreams[1].datapoints[0].value;
        that.setData({
          // random:e.data.data.datastreams[1].datapoints[0].value,
        });
        console.log("randomyy==", e.data.data.datastreams[1].datapoints[0].value);
  
        xAxisArray.push(cc);
        yAxisArray.push(ra);
  
        console.log("random=", ra);
  
        //仅保留最新的7个数据
        if (xAxisArray.length > 7) {
          xAxisArray = xAxisArray.slice(xAxisArray.length - 7);
          yAxisArray = yAxisArray.slice(yAxisArray.length - 7);
        }
  
        //利用 myChart 直接绘制曲线
        setOption(that.myChart, xAxisArray, yAxisArray);
      }
    });
  },
  

  
}); 
 // 将日期对象转换为时分秒形式
function convertTime(date) {
  var hour =addZero(date.getHours());
  var minute = addZero(date.getMinutes());
  var second = addZero(date.getSeconds());
  return hour + ":" + minute + ":" + second;
}

// 如果数字小于10，在前面添加一个0，确保两位数字的格式
function addZero(num) {
  if (num < 10) {
    return "0" + num;
  } else {
    return num;
  }
}