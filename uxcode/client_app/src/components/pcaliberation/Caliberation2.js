import React, { Component } from 'react';
import PropTypes, { array } from 'prop-types';
import { Line } from 'react-chartjs-2';

export default class Caliberation2 extends Component {

    constructor(props) {
        super(props)

        this.totalSamplesOnChart = 2048;

        this.ch1Array = [];
        this.ch2Array = [];
        this.ch3Array = [];

        this.isSocketDataArrayAvaiable = true;
        this.stopRealTime = false;
        this.socketDataArray = [];

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
                    }
                ]
            },
            second_plot_data: {
                labels: this.tmp1,
                datasets: [
                    {
                        label: 'Channel 2',
                        data: this.tmp1
                    }
                ]
            },
            third_plot_data: {
                labels: this.tmp1,
                datasets: [
                    {
                        label: 'Channel 3',
                        data: this.tmp1
                    }
                ]
            },
            plot_options: {
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
                            min: -4,
                            beginAtZero: true,
                            steps: 0.00001,
                            max: 4
                        }
                    }]
                },
                title: {
                    display: true,
                    text: 'Channel 1 Data'
                }
            }
        };
    };


    componentDidMount = () => {
        console.log("Component mounted");

        for (var i = 0; i < this.totalSamplesOnChart; i++) {
            this.ch1Array.push(0.0);
            this.ch2Array.push(0.0);
            this.ch3Array.push(0.0);
        }

        // setTimeout(window.startSocket(), 1);
        // setTimeout(this.getTcpScoketData.bind(this), 1);
        // this.start_time = new Date().getTime();

        // window.sendDataToSocket("real_time_data",null);
        this.showRealTimeData();

    }

    showRealTimeData = () => {

        const { ipcRenderer } = window.require("electron");
        this.startSocketReading(ipcRenderer);
        setTimeout(this.startRenderingGraphs, 100);
        // this.startRenderingGraphs();
        // while (isDataArrayFree() == false) {
        // }
        // var status = tcpScoketData("write", data);
        // if (status != 1) {
        //     while (status != 1) {
        //         status = tcpScoketData("write", data);
        //     }
        // }

    }

    startSocketReading = (ipcRenderer) => {
        ipcRenderer.send("socket_data_send", "real_time_data");
        ipcRenderer.on('real_time_data', function (event, data) {
            var jsonObject = JSON.parse(String(data));
            if (jsonObject.type == "real_time_data") {
                for (let index = 0; index < jsonObject.total_samples; index++) {
                    this.ch1Array.push(jsonObject.ch_v1[index]);
                    this.ch2Array.push(jsonObject.ch_v2[index]);
                    this.ch3Array.push(jsonObject.ch_v3[index]);
                }
            }
        }.bind(this));
    }

    startRenderingGraphs = (data) => {
        while (!this.stopRealTime) {
            console.log("YOYO 1", new Date().getTime(),"  --  ", this.ch1Array.length,"  --  ",  this.totalSamplesOnChart);
            if (this.ch1Array.length > this.totalSamplesOnChart) {
                var tmp = this.ch1Array.length - this.totalSamplesOnChart;
                this.ch1Array.splice(0, tmp);
                tmp = this.ch2Array.length - this.totalSamplesOnChart;
                this.ch2Array.splice(0, tmp);
                tmp = this.ch3Array.length - this.totalSamplesOnChart;
                this.ch3Array.splice(0, tmp);
                this.setDataToChart();
            }
            
            console.log("YOYO 2", new Date().getTime(),"  --  ", this.ch1Array.length,"  --  ",  this.totalSamplesOnChart);
        }

    }

    // getTcpScoketData = () => {
    //     while (this.isSocketDataArrayAvaiable == false) {
    //     }
    //     var data = window.getScoketData('read', null);
    //     if (data.length > 0) {
    //         console.log("Data in React : " + data.length + ' at ' + new Date().getTime());
    //         for (var i = 0; i < data.length; i++) {
    //             this.addDataToArrays(data[i]);
    //         }
    //         this.setDataToChartOne();
    //         this.setDataToChartTwo();
    //     }
    //     setTimeout(this.getTcpScoketData.bind(this), 1);
    // }



    // addDataToArrays = (val) => {
    //     var jsonObject = JSON.parse(String(val));
    //     if (jsonObject.type == "real_time_data") {

    //         for (let index = 0; index < jsonObject.total_samples; index++) {
    //             this.ch1Array.push(jsonObject.ch_v1[index]);
    //             this.ch2Array.push(jsonObject.ch_v2[index]);
    //             this.ch3Array.push(jsonObject.ch_v2[index]);
    //         }
    //     }
    // }

    setDataToChart = () => {
        this.setState({
            first_plot_data: {
                datasets: [
                    {
                        label: 'Channel 1',
                        fill: false,
                        backgroundColor: 'rgba(75,192,192,0.4)',
                        borderColor: 'rgba(75,192,192,1)',
                        data: this.getChannelData(1)
                    }
                ]
            },
            second_plot_data: {
                datasets: [
                    {
                        label: 'Channel 2',
                        fill: false,
                        backgroundColor: 'rgba(75,192,192,0.4)',
                        borderColor: 'rgba(75,192,192,1)',
                        data: this.getChannelData(2)
                    }
                ]
            },
            third_plot_data: {
                datasets: [
                    {
                        label: 'Channel 3',
                        fill: false,
                        backgroundColor: 'rgba(75,192,192,0.4)',
                        borderColor: 'rgba(75,192,192,1)',
                        data: this.getChannelData(3)
                    }
                ]
            }
        });
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
        } else if (val == 3) {
            for (var i = 0; i < this.ch3Array.length; i++) {
                ar.push(this.ch3Array[i])
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
                            <Line data={this.state.first_plot_data} options={this.state.plot_options} height={40} />
                        </div>
                        <div style={{ flex: 1 }}>
                            <Line data={this.state.second_plot_data} options={this.state.plot_options} height={40} />
                        </div>
                        <div style={{ flex: 1 }}>
                            <Line data={this.state.third_plot_data} options={this.state.plot_options} height={40} />
                        </div>

                    </div>
                </div>
            </div>
        )
    }
}



