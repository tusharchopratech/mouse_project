import React, { Component } from 'react';
import PropTypes, { array } from 'prop-types';
import { Line } from 'react-chartjs-2';

export default class RealTimeData extends Component {


  constructor(props) {
    super(props)

    this.totalSamplesOnChart = 230;


    this.ch1Array = [];
    this.ch2Array = [];
    this.ch3Array = [];
    this.ch4Array = [];
    this.leftClickArray = [];
    this.rightClickArray = [];

    this.tmp1 = [1];
    this.tmp2 = [2];
    this.tmp3 = [3];
    this.tmp4 = [4];
    this.tmp5 = [5];
    this.tmp6 = [6];
    this.state = {
      data: {
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
            label: 'Channel 3',
            data: this.tmp
          },
          {
            label: 'Channel 4',
            data: this.tmp
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
      options: {
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
      }
    };
  };


  componentDidMount = () => {
    console.log("Component mounted");
    window.startSocket(this.socketData);
    this.start_time = new Date().getTime();
  }



  socketData = (val) => {
    var jsonObject = JSON.parse(String(val));
    if (jsonObject.type == "real_time_data") {

      this.ch1Array.push(jsonObject.ch_v1);
      if (this.ch1Array.length > this.totalSamplesOnChart) {
        this.ch1Array.splice(0, 1);
      }

      this.ch2Array.push(jsonObject.ch_v2);
      if (this.ch2Array.length > this.totalSamplesOnChart) {
        this.ch2Array.splice(0, 1);
      }

      this.ch3Array.push(jsonObject.ch_v3);
      if (this.ch3Array.length > this.totalSamplesOnChart) {
        this.ch3Array.splice(0, 1);
      }

      this.ch4Array.push(jsonObject.ch_v4);
      if (this.ch4Array.length > this.totalSamplesOnChart) {
        this.ch4Array.splice(0, 1);
      }

      this.leftClickArray.push(jsonObject.left_click);
      if (this.leftClickArray.length > this.totalSamplesOnChart) {
        this.leftClickArray.splice(0, 1);
      }

      this.rightClickArray.push(jsonObject.right_click);
      if (this.rightClickArray.length > this.totalSamplesOnChart) {
        this.rightClickArray.splice(0, 1);
      }

      this.setDataToChart();
    }

  }

  setDataToChart = () => {
    this.setState({
      data: {
        datasets: [
          {
            label: 'Channel 1',
            fill: false,
            backgroundColor: 'rgba(75,192,192,0.4)',
            borderColor: 'rgba(75,192,192,1)',
            data: this.getChannel1Data()
          }, 
          {
            label: 'Channel 2',
            fill: false,
            backgroundColor: '#99A9A9A9',
            borderColor: '#A9A9A9',
            data: this.getChannel2Data()
          }, 
          // {
          //   label: 'Channel 3',
          //   fill: false,
          //   backgroundColor: 'rgba(75,192,192,0.4)',
          //   borderColor: 'rgba(75,192,192,1)',
          //   data: this.getChannel3Data()
          // }, {
          //   label: 'Channel 4',
          //   fill: false,
          //   backgroundColor: 'rgba(75,192,192,0.4)',
          //   borderColor: 'rgba(75,192,192,1)',
          //   data: this.getChannel4Data()
          // }
          {
            label: 'Left Click',
            fill: false,
            backgroundColor: '#99ff0000',
            borderColor: '#ff0000',
            data: this.getLeftClickData()
          }, 
          {
            label: 'Right Click',
            fill: false,
            backgroundColor: '#99006600',
            borderColor: '#006600',
            data: this.getRightClickData()
          }, 
        ]
      }
    });
  }

  getChannel1Data = () => {
    var ar = [];
    for (var i = 0; i < this.ch1Array.length; i++) {
      ar.push(this.ch1Array[i])
    }
    return ar;
  }

  getChannel2Data = () => {
    var ar2 = [];
    for (var i = 0; i < this.ch2Array.length; i++) {
      ar2.push(this.ch2Array[i])
    }
    return ar2;
  }

  getChannel3Data = () => {
    var ar3 = [];
    for (var i = 0; i < this.ch3Array.length; i++) {
      ar3.push(this.ch3Array[i])
    }
    return ar3;
  }

  getChannel4Data = () => {
    var ar4 = [];
    for (var i = 0; i < this.ch4Array.length; i++) {
      ar4.push(this.ch4Array[i])
    }
    return ar4;
  }

  getLeftClickData = () => {
    var ar5 = [];
    for (var i = 0; i < this.leftClickArray.length; i++) {
      ar5.push(this.leftClickArray[i])
    }
    return ar5;
  }

  getRightClickData = () => {
    var ar6 = [];
    for (var i = 0; i < this.rightClickArray.length; i++) {
      ar6.push(this.rightClickArray[i])
    }
    return ar6;
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
          <p></p>


          <div style={{ display: 'flex', justifyContent: 'flex-start' }}>
            <div style={{ flex: 1 }}>
              <Line data={this.state.data} options={this.state.options} />
            </div>
          </div>

          <div style={{ display: 'flex', justifyContent: 'center'}}>
            {/* <Bar
              data={data}
              options={{
                maintainAspectRatio: true
              }}
            /> */}
          </div>

        </div>
      </div>
    )
  }
}



