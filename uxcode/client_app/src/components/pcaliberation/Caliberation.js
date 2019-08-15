import React, { Component } from 'react';
import { withStyles } from '@material-ui/core/styles';
import PropTypes, { array } from 'prop-types';
import Fab from '@material-ui/core/Fab';
import { Line } from 'react-chartjs-2';
import { ReactComponent as HandIconWhite } from '../../images/hand_white.svg';


class Caliberation extends Component {

    constructor(props) {
        super(props)

        this.totalSamplesOnChart = 2048*2;

        this.ch1Array = [];
        this.ch2Array = [];
        this.ch3Array = [];
        this.ch4Array = [];
        this.lCArray = [];
        this.rCArray = [];
        this.tCArray = [];

        this.ch1ArrayTemp = [];
        this.ch2ArrayTemp = [];
        this.ch3ArrayTemp = [];
        this.ch4ArrayTemp = [];
        this.lCArrayTemp = [];
        this.rCArrayTemp = [];
        this.tCArrayTemp = [];

        this.ch1Temp = 0.0;
        this.ch2Temp = 0.0;
        this.ch3Temp = 0.0;
        this.ch4Temp = 0.0;
        this.lCTemp = 0;
        this.rCTemp = 0;
        this.tCTemp = 0;

        this.startRendering = true;
        this.tmp1 = [1];
        this.state = {
            first_plot_data: { labels: this.tmp1, datasets: [{ label: 'Channel 1', data: this.tmp1 }] },
            second_plot_data: { labels: this.tmp1, datasets: [{ label: 'Channel 2', data: this.tmp1 }] },
            third_plot_data: { labels: this.tmp1, datasets: [{ label: 'Channel 3', data: this.tmp1 }] },
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

    startTraining = () => {
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.send("socket_data_send", "stop_raw_real_time_data");
        ipcRenderer.send("socket_data_send", "start_training");
    };

    componentDidMount = () => {
        console.log("Component mounted");
        for (var i = 0; i < this.totalSamplesOnChart; i++) {
            this.ch1Array.push(0.0);
            this.ch2Array.push(0.0);
            this.ch3Array.push(0.0);
            this.ch4Array.push(0.0);
            this.lCArray.push(0.0);
            this.rCArray.push(0.0);
            this.tCArray.push(0.0);
        }
        this.showRealTimeData();
    }

    showRealTimeData = () => {
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.send("socket_data_send", "start_raw_real_time_data");

        ipcRenderer.on('socket_data_received', function (event, data) {
            // console.log(String(data), " at ", new Date().getTime());
            console.log("New Data at ", new Date().getTime());
            var jsonObject = JSON.parse(String(data));
            if (jsonObject.type == "real_time_raw_data") {
                this.ch1Temp = jsonObject.ch_v1[0];
                this.ch2Temp = jsonObject.ch_v2[0];
                this.ch3Temp = jsonObject.ch_v3[0];
                this.ch4Temp = jsonObject.ch_v4[0];
                this.lCTemp = jsonObject.left_click[0];
                this.rCTemp = jsonObject.right_click[0];
                this.tCTemp = jsonObject.thumb_click[0];

                if (this.ch1ArrayTemp.length > 1000 && this.startRendering) {
                    this.startRendering = false;
                    setTimeout(this.startRenderingGraphs2, 10, this.ch1ArrayTemp, this.ch2ArrayTemp, this.ch3ArrayTemp, this.ch4ArrayTemp, this.lCArrayTemp, this.rCArrayTemp, this.tCArrayTemp);
                    this.ch1ArrayTemp = [];
                    this.ch2ArrayTemp = [];
                    this.ch3ArrayTemp = [];
                    this.ch4ArrayTemp = [];
                    this.lCArrayTemp = [];
                    this.rCArrayTemp = [];
                    this.tCArrayTemp = [];
                }
                for (let index = 0; index < jsonObject.total_samples; index++) {
                    this.ch1ArrayTemp.push(jsonObject.ch_v1[index]);
                    this.ch2ArrayTemp.push(jsonObject.ch_v2[index]);
                    this.ch3ArrayTemp.push(jsonObject.ch_v3[index]);
                    this.ch4ArrayTemp.push(jsonObject.ch_v4[index]);
                    this.lCArrayTemp.push(jsonObject.left_click[index]);
                    this.rCArrayTemp.push(jsonObject.right_click[index]);
                    this.tCArrayTemp.push(jsonObject.thumb_click[index]);
                }
            } else if (jsonObject.type == "start_training_success") {
                this.props.callbackSetMainSection('user_training');
            }
        }.bind(this));

        setTimeout(this.startRenderingGraphs, 20);
        // setTimeout( this.startRederingCharts2, 20);
        // this.startRederingCharts2();    
    }

    startRederingCharts2 = () => {

        this.ch1Array.push(this.ch1Temp);
        this.ch2Array.push(this.ch2Temp);
        this.ch3Array.push(this.ch3Temp);
        this.ch4Array.push(this.ch4Temp);
        this.lCArray.push(this.lCTemp);
        this.rCArray.push(this.rCTemp);
        this.tCArray.push(this.tCTemp);
        this.ch1Array.splice(0, 1);
        this.ch2Array.splice(0, 1);
        this.ch3Array.splice(0, 1);
        this.ch4Array.splice(0, 1);
        this.lCArray.splice(0, 1);
        this.rCArray.splice(0, 1);
        this.tCArray.splice(0, 1);
        this.setDataToChart();

    }

    startRenderingGraphs2 = (ch1Data, ch2Data, ch3Data, ch4Data, lC, rC, tC) => {

        this.ch1Array = this.ch1Array.concat(ch1Data);
        this.ch2Array = this.ch2Array.concat(ch2Data);
        this.ch3Array = this.ch3Array.concat(ch3Data);
        this.ch4Array = this.ch4Array.concat(ch4Data);
        this.lCArray = this.lCArray.concat(lC);
        this.rCArray = this.rCArray.concat(rC);
        this.tCArray = this.tCArray.concat(tC);
        this.ch1Array.splice(0, ch1Data.length);
        this.ch2Array.splice(0, ch2Data.length);
        this.ch3Array.splice(0, ch3Data.length);
        this.ch4Array.splice(0, ch4Data.length);
        this.lCArray.splice(0, lC.length);
        this.rCArray.splice(0, rC.length);
        this.tCArray.splice(0, tC.length);

        this.ch2ArrayTemp = [];
        this.ch3ArrayTemp = [];
        this.ch4ArrayTemp = [];
        this.lCArrayTemp = [];
        this.rCArrayTemp = [];
        this.tCArrayTemp = [];

        this.setDataToChart();
        this.startRendering = true;
    }

    startRenderingGraphs = () => {

        var ch1Data = this.ch1ArrayTemp;
        var ch2Data = this.ch2ArrayTemp;
        var ch3Data = this.ch3ArrayTemp;
        var ch4Data = this.ch4ArrayTemp;
        var lC = this.lCArrayTemp;
        var rC = this.rCArrayTemp;
        var tC = this.tCArrayTemp;

        this.ch1Array = this.ch1Array.concat(ch1Data);
        this.ch2Array = this.ch2Array.concat(ch2Data);
        this.ch3Array = this.ch3Array.concat(ch3Data);
        this.ch4Array = this.ch4Array.concat(ch4Data);
        this.lCArray = this.lCArray.concat(lC);
        this.rCArray = this.rCArray.concat(rC);
        this.tCArray = this.tCArray.concat(tC);
        this.ch1Array.splice(0, ch1Data.length);
        this.ch2Array.splice(0, ch2Data.length);
        this.ch3Array.splice(0, ch3Data.length);
        this.ch4Array.splice(0, ch4Data.length);
        this.lCArray.splice(0, lC.length);
        this.rCArray.splice(0, rC.length);
        this.tCArray.splice(0, tC.length);

        this.ch2ArrayTemp = [];
        this.ch3ArrayTemp = [];
        this.ch4ArrayTemp = [];
        this.lCArrayTemp = [];
        this.rCArrayTemp = [];
        this.tCArrayTemp = [];

        this.setDataToChart();
    }

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
                    },
                    {
                        label: 'Left Click',
                        fill: false,
                        backgroundColor: '#99ff0000',
                        borderColor: '#ff0000',
                        data: this.getClickData("left", 3)
                    },
                    {
                        label: 'Right Click',
                        fill: false,
                        backgroundColor: '#99006600',
                        borderColor: '#006600',
                        data: this.getClickData("right", 3)
                    },
                    {
                        label: 'Thumb Click',
                        fill: false,
                        backgroundColor: '#99ff0000',
                        borderColor: '#ff0000',
                        data: this.getClickData("thumb", 3)
                    },
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
                    },
                    {
                        label: 'Left Click',
                        fill: false,
                        backgroundColor: '#99ff0000',
                        borderColor: '#ff0000',
                        data: this.getClickData("left", 3)
                    },
                    {
                        label: 'Right Click',
                        fill: false,
                        backgroundColor: '#99006600',
                        borderColor: '#006600',
                        data: this.getClickData("right", 3)
                    },
                    {
                        label: 'Thumb Click',
                        fill: false,
                        backgroundColor: '#99ff0000',
                        borderColor: '#ff0000',
                        data: this.getClickData("thumb", 3)
                    },

                ]
            },
            third_plot_data: {
                datasets: [
                    {
                        label: 'Channel 3',
                        fill: false,
                        backgroundColor: 'rgba(75,192,192,0.4)',
                        borderColor: 'rgba(75,192,192,1)',
                        data: this.getChannelData(4)
                    },
                    {
                        label: 'Left Click',
                        fill: false,
                        backgroundColor: '#99ff0000',
                        borderColor: '#ff0000',
                        data: this.getClickData("left", 3)
                    },
                    {
                        label: 'Right Click',
                        fill: false,
                        backgroundColor: '#99006600',
                        borderColor: '#006600',
                        data: this.getClickData("right", 3)
                    },
                    {
                        label: 'Thumb Click',
                        fill: false,
                        backgroundColor: '#99ff0000',
                        borderColor: '#ff0000',
                        data: this.getClickData("thumb", 3)
                    },
                ]
            },
        });

        // setTimeout(this.startRenderingGraphs, 2);

        // setTimeout(this.startRederingCharts2, 2);
        // this.startRederingCharts2();
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
        } else if (val == 4) {
            for (var i = 0; i < this.ch4Array.length; i++) {
                ar.push(this.ch4Array[i])
            }
        }
        return ar;
    }

    getClickData = (val, amplitudeMultiplier) => {
        var ar6 = [];
        if (val == "right") {
            for (var i = 0; i < this.rCArray.length; i++) {
                ar6.push(this.rCArray[i] * amplitudeMultiplier)
            }
        } else if (val == "left") {
            for (var i = 0; i < this.lCArray.length; i++) {
                ar6.push(this.lCArray[i] * amplitudeMultiplier)
            }
        } else if (val == "thumb") {
            for (var i = 0; i < this.tCArray.length; i++) {
                ar6.push(this.tCArray[i] * amplitudeMultiplier)
            }
        }
        return ar6;
    }


    render() {
        const { classes } = this.props;
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
                            <Line data={this.state.first_plot_data} options={this.state.plot_options} height={60} />
                        </div>
                        <div style={{ flex: 1 }}>
                            <Line data={this.state.second_plot_data} options={this.state.plot_options} height={60} />
                        </div>
                        <div style={{ flex: 1 }}>
                            <Line data={this.state.third_plot_data} options={this.state.plot_options} height={60} />
                        </div>

                    </div>

                    <div style={{ display: 'flex', justifyContent: 'center', paddingTop: 30 }}>
                        <Fab variant="extended" color="primary" aria-label="Add" onClick={this.startTraining} className={classes.margin}>
                            <HandIconWhite className={classes.extendedIcon} />
                            Next Step ( Click Training )
                        </Fab>
                    </div>

                </div>
            </div>
        )
    }
}

const styles = theme => ({
    margin: {
        margin: theme.spacing.unit,
    },
    extendedIcon: {
        marginRight: theme.spacing.unit,
    },
});

export default withStyles(styles, { withTheme: true })(Caliberation);
