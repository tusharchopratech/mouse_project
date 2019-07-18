import React, { Component } from 'react';
import { withStyles } from '@material-ui/core/styles';
import PropTypes, { array } from 'prop-types';
import Fab from '@material-ui/core/Fab';
import { Line } from 'react-chartjs-2';
import { ReactComponent as HandIconWhite } from '../../images/hand_white.svg';


class Caliberation extends Component {

    constructor(props) {
        super(props)

        this.totalSamplesOnChart = 2048;
        this.ch1Array = [];
        this.ch2Array = [];
        this.ch3Array = [];
        this.ch1ArrayTemp = [];
        this.ch2ArrayTemp = [];
        this.ch3ArrayTemp = [];
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
        ipcRenderer.send("socket_data_send", "stop_real_time_data");
        ipcRenderer.send("socket_data_send", "start_training");
    };

    componentDidMount = () => {
        console.log("Component mounted");
        for (var i = 0; i < this.totalSamplesOnChart; i++) {
            this.ch1Array.push(0.0);
            this.ch2Array.push(0.0);
            this.ch3Array.push(0.0);
        }
        this.showRealTimeData();
    }

    showRealTimeData = () => {
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.send("socket_data_send", "start_real_time_data");
        ipcRenderer.on('socket_data_received', function (event, data) {
            // console.log("New Data at ", new Date().getTime());
            var jsonObject = JSON.parse(String(data));
            if (jsonObject.type == "real_time_data") {
                if (this.startRendering) {
                    this.startRendering = false;
                    setTimeout(this.startRenderingGraphs, 50, this.ch1ArrayTemp, this.ch2ArrayTemp, this.ch3ArrayTemp);
                    this.ch1ArrayTemp = [];
                    this.ch2ArrayTemp = [];
                    this.ch3ArrayTemp = [];
                }
                for (let index = 0; index < jsonObject.total_samples; index++) {
                    this.ch1ArrayTemp.push(jsonObject.ch_v1[index]);
                    this.ch2ArrayTemp.push(jsonObject.ch_v2[index]);
                    this.ch3ArrayTemp.push(jsonObject.ch_v3[index]);
                }
            } else if (jsonObject.type == "training_started") {
                this.props.callbackSetMainSection('user_training');
            }
        }.bind(this));
    }

    startRenderingGraphs = (ch1Data, ch2Data, ch3Data) => {
        this.ch1Array = this.ch1Array.concat(ch1Data);
        this.ch2Array = this.ch2Array.concat(ch2Data);
        this.ch3Array = this.ch3Array.concat(ch3Data);
        this.ch1Array.splice(0, ch1Data.length);
        this.ch2Array.splice(0, ch2Data.length);
        this.ch3Array.splice(0, ch3Data.length);
        this.setDataToChart();
        this.startRendering = true;
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
                            <Line data={this.state.first_plot_data} options={this.state.plot_options} height={40} />
                        </div>
                        <div style={{ flex: 1 }}>
                            <Line data={this.state.second_plot_data} options={this.state.plot_options} height={40} />
                        </div>
                        <div style={{ flex: 1 }}>
                            <Line data={this.state.third_plot_data} options={this.state.plot_options} height={40} />
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
