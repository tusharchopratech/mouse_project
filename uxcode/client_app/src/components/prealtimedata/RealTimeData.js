import React, { Component } from 'react';
import PropTypes, { array } from 'prop-types';
import { Line } from 'react-chartjs-2';

export default class RealTimeData extends Component {


  constructor(props) {
    super(props)

    this.totalSamplesOnChartOne = 1000;
    this.totalSamplesOnChartTwo = 1000;

    this.ch1Array = [];
    this.ch2Array = [];
    this.leftClickArray = [];
    this.rightClickArray = [];

    this.ch1ArrayTkeo = [];
    this.ch2ArrayTkeo = [];
    this.leftClickArrayTkeo = [];
    this.rightClickArrayTkeo = [];

    this.tmp1 = [1];
    this.tmp2 = [2];
    this.tmp3 = [3];
    this.tmp4 = [4];
    this.tmp5 = [5];
    this.tmp6 = [6];
    this.state = {
      first_plot_data: {
        labels: this.tmp1,
        datasets: [
          {
            label: 'Channel 1',
            data: this.tmp1
          },
          {
            label: 'Channel 2',

            data: this.tmp2
          },
          {
            label: 'Left Click',
            data: this.tmp5
          },
          {
            label: 'Right Click',
            data: this.tmp6
          },
        ]
      },
      second_plot_data: {
        labels: this.tmp1,
        datasets: [
          {
            label: 'Tkeo 1',
            data: this.tmp1
          },
          {
            label: 'Tkeo 2',
            data: this.tmp2
          },
          {
            label: 'Left Click',
            data: this.tmp5
          },
          {
            label: 'Right Click',
            data: this.tmp6
          },
        ]
      },
      first_plot_options: {
        elements: {
          point: {
            radius: 0
          }
        },
        animation: {
          duration: 0
        },
        responsive: true,
        legend: {
          position: 'bottom',
        },
        hover: {
          mode: 'label'
        },
        scales: {
          xAxes: [{
            gridLines: {
              color: "rgba(0, 0, 0, 0)",
            },
            display: true,
            scaleLabel: {
              display: true,
              labelString: 'Time'
            },
            ticks: {
              display: false
            }
          }],
          yAxes: [{
            display: true,
            scaleLabel: {
              display: true,
              labelString: 'Voltage'
            },
            ticks: {
              min: -3,
              beginAtZero: true,
              steps: 0.000001,
              max: 3
            }
          }]
        },
        title: {
          display: true,
          text: 'Real Time Data EMG & Mouse Data'
        }
      },
      second_plot_options: {
        elements: {
          point: {
            radius: 0
          }
        },
        animation: {
          duration: 0
        },
        responsive: true,
        legend: {
          position: 'bottom',
        },
        hover: {
          mode: 'label'
        },
        scales: {
          xAxes: [{
            gridLines: {
              color: "rgba(0, 0, 0, 0)",
            },
            display: true,
            scaleLabel: {
              display: true,
              labelString: 'Time'
            },
            ticks: {
              display: false
            }
          }],
          yAxes: [{
            display: true,
            scaleLabel: {
              display: true,
              labelString: 'Voltage'
            },
            ticks: {
              beginAtZero: true,
              min: -0.05,
              max: 0.05
            }
          }]
        },
        title: {
          display: true,
          text: 'Real Time Tkeo & Mouse Data'
        }
      }
    };
  };


  componentDidMount = () => {
    console.log("Component mounted");

    for (var i = 0; i < this.totalSamplesOnChartOne; i++) {
      this.ch1Array.push(0.0);
      this.ch2Array.push(0.0);
      this.leftClickArray.push(0.0);
      this.rightClickArray.push(0.0);
    }

    for (var i = 0; i < this.totalSamplesOnChartTwo; i++) {
      this.ch1ArrayTkeo.push(0.0);
      this.ch2ArrayTkeo.push(0.0);
      this.leftClickArrayTkeo.push(0.0);
      this.rightClickArrayTkeo.push(0.0);
    }

    setTimeout(window.startSocket(), 1);
    // setTimeout(this.getTcpScoketData.bind(this), 1);
    this.start_time = new Date().getTime();
  }

  getTcpScoketData = () => {
    while (window.isDataArrayFree() == false) {
    }
    var data = window.tcpScoketData('read', null);
    if (data.length > 0) {
      console.log("Data in React : " + data.length + ' at ' + new Date().getTime());
      for (var i = 0; i < data.length; i++) {
        this.addDataToArrays(data[i]);
      }
      this.setDataToChartOne();
      this.setDataToChartTwo();
    }
    setTimeout(this.getTcpScoketData.bind(this), 1);
  }



  addDataToArrays = (val) => {
    var jsonObject = JSON.parse(String(val));
    if (jsonObject.type == "real_time_data") {

      this.ch1Array.push(jsonObject.ch_v1[0]);
      this.ch1Array.push(jsonObject.ch_v1[1]);
      this.ch1Array.push(jsonObject.ch_v1[2]);
      this.ch1Array.splice(0, 1);
      this.ch1Array.splice(0, 1);
      this.ch1Array.splice(0, 1);

      this.ch2Array.push(jsonObject.ch_v2[0]);
      this.ch2Array.push(jsonObject.ch_v2[1]);
      this.ch2Array.push(jsonObject.ch_v2[2]);
      this.ch2Array.splice(0, 1);
      this.ch2Array.splice(0, 1);
      this.ch2Array.splice(0, 1);

      this.leftClickArray.push(jsonObject.left_click);
      this.leftClickArray.push(jsonObject.left_click);
      this.leftClickArray.push(jsonObject.left_click);
      this.leftClickArray.splice(0, 1);
      this.leftClickArray.splice(0, 1);
      this.leftClickArray.splice(0, 1);

      this.rightClickArray.push(jsonObject.right_click);
      this.rightClickArray.push(jsonObject.right_click);
      this.rightClickArray.push(jsonObject.right_click);
      this.rightClickArray.splice(0, 1);
      this.rightClickArray.splice(0, 1);
      this.rightClickArray.splice(0, 1);

      this.ch1ArrayTkeo.push(jsonObject.ch_v1_tkeo);
      this.ch1ArrayTkeo.push(jsonObject.ch_v1_tkeo);
      this.ch1ArrayTkeo.push(jsonObject.ch_v1_tkeo);
      this.ch1ArrayTkeo.splice(0, 1);
      this.ch1ArrayTkeo.splice(0, 1);
      this.ch1ArrayTkeo.splice(0, 1);
      this.ch2ArrayTkeo.push(jsonObject.ch_v2_tkeo);
      this.ch2ArrayTkeo.push(jsonObject.ch_v2_tkeo);
      this.ch2ArrayTkeo.push(jsonObject.ch_v2_tkeo);
      this.ch2ArrayTkeo.splice(0, 1);
      this.ch2ArrayTkeo.splice(0, 1);
      this.ch2ArrayTkeo.splice(0, 1);
    }
  }

  setDataToChartOne = () => {
    this.setState({
      first_plot_data: {
        datasets: [
          {
            label: 'Channel 1',
            fill: false,
            backgroundColor: 'rgba(75,192,192,0.4)',
            borderColor: 'rgba(75,192,192,1)',
            data: this.getChannelData(1)
          },
          {
            label: 'Channel 2',
            fill: false,
            backgroundColor: '#99A9A9A9',
            borderColor: '#A9A9A9',
            data: this.getChannelData(2)
          },
          {
            label: 'Left Click',
            fill: false,
            backgroundColor: '#99ff0000',
            borderColor: '#ff0000',
            data: this.getClickData("left", 1)
          },
          {
            label: 'Right Click',
            fill: false,
            backgroundColor: '#99006600',
            borderColor: '#006600',
            data: this.getClickData("right", 1)
          },
        ]
      }
    });
  }

  setDataToChartTwo = () => {
    this.setState({
      second_plot_data: {
        datasets: [
          {
            label: 'Channel 1 Tkeo',
            fill: false,
            backgroundColor: 'rgba(75,192,192,0.4)',
            borderColor: 'rgba(75,192,192,1)',
            data: this.getChannelDataTkeo(1)
          },
          {
            label: 'Channel 2 Tkeo',
            fill: false,
            backgroundColor: '#99A9A9A9',
            borderColor: '#A9A9A9',
            data: this.getChannelDataTkeo(2)
          },
          {
            label: 'Left Click',
            fill: false,
            backgroundColor: '#99ff0000',
            borderColor: '#ff0000',
            data: this.getClickData("left", 0.005)
          },
          {
            label: 'Right Click',
            fill: false,
            backgroundColor: '#99006600',
            borderColor: '#006600',
            data: this.getClickData("right", 0.006)
          },
        ]
      }
    });
  }


  getClickData = (val, amplitudeMultiplier) => {
    var ar6 = [];
    if (val == "right") {
      for (var i = 0; i < this.rightClickArray.length; i++) {
        ar6.push(this.rightClickArray[i] * amplitudeMultiplier)
      }
    } else if (val == "left") {
      for (var i = 0; i < this.leftClickArray.length; i++) {
        ar6.push(this.leftClickArray[i] * amplitudeMultiplier)
      }
    }
    return ar6;
  }

  getChannelData = (val) => {
    var ar = [];
    if (val == 1) {
      for (var i = 0; i < this.ch1Array.length; i++) {
        ar.push(this.ch1Array[i])
      }
    } else if (val == 2) {
      for (var i = 0; i < this.ch2Array.length; i++) {
        ar.push(this.ch2Array[i])
      }
    }
    return ar;
  }


  getChannelDataTkeo = (val) => {
    var ar = [];
    if (val == 1) {
      for (var i = 0; i < this.ch1ArrayTkeo.length; i++) {
        ar.push(this.ch1ArrayTkeo[i])
      }
    } else if (val == 2) {
      for (var i = 0; i < this.ch2ArrayTkeo.length; i++) {
        ar.push(this.ch2ArrayTkeo[i])
      }
    }
    return ar;
  }


  render() {

    return (
      <div style={{ height: '100%', width: '100%' }}>
        <div style={{
          display: 'flex',
          flexDirection: 'column',
          justifyContent: 'center',
          height: '100%',
          padding: '5%',
        }}>
          <div style={{ display: 'flex', justifyContent: 'flex-start', flexDirection: 'column' }}>

            <div style={{ flex: 1 }}>
              <Line data={this.state.first_plot_data} options={this.state.first_plot_options} height={70} />
            </div>
            <div style={{ flex: 1 }}>
              <Line data={this.state.second_plot_data} options={this.state.second_plot_options} height={70} />
            </div>

          </div>
        </div>
      </div>
    )
  }
}



