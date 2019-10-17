import React, {Component} from "react";
import {withStyles} from "@material-ui/core/styles";
import PropTypes from "prop-types";
import {Line} from "react-chartjs-2";

class SignalsComp extends Component {
  constructor(props) {
    super(props);

    this.parentComponentName = this.props.parentComponentName;
    this.totalSamplesOnChart = 2048 * 2;

    this.ch1Array = [];
    this.ch2Array = [];
    this.ch3Array = [];
    this.ch4Array = [];
    this.lCArray = [];
    this.rCArray = [];
    this.tCArray = [];
    this.iCArray = [];

    this.ch1ArrayTemp = [];
    this.ch2ArrayTemp = [];
    this.ch3ArrayTemp = [];
    this.ch4ArrayTemp = [];
    this.lCArrayTemp = [];
    this.rCArrayTemp = [];
    this.tCArrayTemp = [];
    this.iCArrayTemp = [];

    this.tmp1 = [1];
    this.tmp2 = [2];
    this.tmp3 = [9, 8];
    this.tmp4 = [4, 3, 3];
    this.state = {
      first_plot_data: {labels: this.tmp1, datasets: [{label: "Channel 1", data: this.tmp1}]},
      second_plot_data: {labels: this.tmp2, datasets: [{label: "Channel 2", data: this.tmp2}]},
      third_plot_data: {labels: this.tmp3, datasets: [{label: "Channel 3", data: this.tmp3}]},
      fourth_plot_data: {labels: this.tmp4, datasets: [{label: "Channel 4", data: this.tmp4}]},
      plot_options: {
        elements: {point: {radius: 0}},
        animation: {duration: 0},
        responsive: true,
        legend: {position: "bottom"},
        hover: {mode: "label"},
        scales: {
          xAxes: [
            {
              gridLines: {color: "rgba(0, 0, 0, 0)"},
              display: true,
              scaleLabel: {display: true, labelString: "Time"},
              ticks: {display: false}
            }
          ],
          yAxes: [
            {
              display: true,
              scaleLabel: {display: true, labelString: "Voltage"},
              ticks: {min: -4, beginAtZero: true, steps: 0.00001, max: 4}
            }
          ]
        },
        title: {display: true, text: ""},
        borderWidth: 10
      }
    };
    this.fourthLabel = "Thumb Click";
    this.fourthMultiplier = 3;
    if (this.parentComponentName == "real_time_game_play") {
      this.fourthLabel = "Impulse Click";
      this.fourthMultiplier = 4;
    }
  }

  componentDidMount = () => {
    this.props.onRef(this);
    console.log("Signal Component Mounted");

    for (var i = 0; i < this.totalSamplesOnChart; i++) {
      this.ch1Array.push(0.0);
      this.ch2Array.push(0.0);
      this.ch3Array.push(0.0);
      this.ch4Array.push(0.0);
      this.lCArray.push(0.0);
      this.rCArray.push(0.0);
      this.tCArray.push(0.0);
      this.iCArray.push(0.0);
    }
    this.setDataToChart();
    setInterval(this.renderGraphs, 600);
  };

  componentWillUnmount = () => {
    console.log("Signal Component Unmounted!!");
  };

  addPoints = (jsonObject) => {
    console.log(jsonObject);
    for (let index = 0; index < jsonObject.total_samples; index++) {
      this.ch1ArrayTemp.push(jsonObject.ch_v1[index]);
      this.ch2ArrayTemp.push(jsonObject.ch_v2[index]);
      this.ch3ArrayTemp.push(jsonObject.ch_v3[index]);
      this.ch4ArrayTemp.push(jsonObject.ch_v4[index]);
      this.lCArrayTemp.push(jsonObject.left_click[index]);
      this.rCArrayTemp.push(jsonObject.right_click[index]);
      this.tCArrayTemp.push(jsonObject.thumb_click[index]);
      if (this.parentComponentName == "real_time_game_play") {
        this.iCArrayTemp.push(jsonObject.impulse_click[index]);
      }
    }
  };

  renderGraphs = () => {
    var size = this.ch1ArrayTemp.length;
    if (size > 1000) {
      //   console.log("\n\n\n I RUN");
      this.ch1Array = this.ch1Array.concat(this.ch1ArrayTemp.splice(0, size));
      this.ch2Array = this.ch2Array.concat(this.ch2ArrayTemp.splice(0, size));
      this.ch3Array = this.ch3Array.concat(this.ch3ArrayTemp.splice(0, size));
      this.ch4Array = this.ch4Array.concat(this.ch4ArrayTemp.splice(0, size));
      this.lCArray = this.lCArray.concat(this.lCArrayTemp.splice(0, size));
      this.rCArray = this.rCArray.concat(this.rCArrayTemp.splice(0, size));
      this.tCArray = this.tCArray.concat(this.tCArrayTemp.splice(0, size));
      if (this.parentComponentName == "real_time_game_play") {
        this.iCArray = this.iCArray.concat(this.iCArrayTemp.splice(0, size));
      }

      this.ch1Array.splice(0, size);
      this.ch2Array.splice(0, size);
      this.ch3Array.splice(0, size);
      this.ch4Array.splice(0, size);
      this.lCArray.splice(0, size);
      this.rCArray.splice(0, size);
      this.tCArray.splice(0, size);
      if (this.parentComponentName == "real_time_game_play") {
        this.iCArray.splice(0, size);
      }
      this.setDataToChart();
    }
  };

  setDataToChart = () => {
    this.setState({
      first_plot_data: {
        datasets: [
          {label: "Channel 1", fill: false, backgroundColor: "#99000000", borderColor: "#4bc0c0", borderWidth: 1, data: this.getChannelData(1)},
          {label: "Left Click", fill: false, backgroundColor: "#99000000", borderColor: "#ff0000", borderWidth: 1, data: this.getClickData("left", 3)},
          {label: "Right Click", fill: false, backgroundColor: "#99000000", borderColor: "#006600", borderWidth: 1, data: this.getClickData("right", 3)},
          {
            label: this.fourthLabel,
            fill: false,
            backgroundColor: "#99000000",
            borderColor: "#00468b",
            borderWidth: 1,
            data: this.getClickData("fourth", this.fourthMultiplier)
          }
        ]
      },
      second_plot_data: {
        datasets: [
          {label: "Channel 2", fill: false, backgroundColor: "#99000000", borderColor: "#4bc0c0", borderWidth: 1, data: this.getChannelData(2)},
          {label: "Left Click", fill: false, backgroundColor: "#99ff0000", borderColor: "#ff0000", borderWidth: 1, data: this.getClickData("left", 3)},
          {label: "Right Click", fill: false, backgroundColor: "#99006600", borderColor: "#006600", borderWidth: 1, data: this.getClickData("right", 3)},
          {
            label: this.fourthLabel,
            fill: false,
            backgroundColor: "#99000000",
            borderColor: "#00468b",
            borderWidth: 1,
            data: this.getClickData("fourth", this.fourthMultiplier)
          }
        ]
      },
      third_plot_data: {
        datasets: [
          {label: "Channel 3", fill: false, backgroundColor: "#99000000", borderColor: "#4bc0c0", borderWidth: 1, data: this.getChannelData(3)},
          {label: "Left Click", fill: false, backgroundColor: "#99ff0000", borderColor: "#ff0000", borderWidth: 1, data: this.getClickData("left", 3)},
          {label: "Right Click", fill: false, backgroundColor: "#99006600", borderColor: "#006600", borderWidth: 1, data: this.getClickData("right", 3)},
          {
            label: this.fourthLabel,
            fill: false,
            backgroundColor: "#99000000",
            borderColor: "#00468b",
            borderWidth: 1,
            data: this.getClickData("fourth", this.fourthMultiplier)
          }
        ]
      },
      fourth_plot_data: {
        datasets: [
          {label: "Channel 4", fill: false, backgroundColor: "#99000000", borderColor: "#4bc0c0", borderWidth: 1, data: this.getChannelData(4)},
          {label: "Left Click", fill: false, backgroundColor: "#99ff0000", borderColor: "#ff0000", borderWidth: 1, data: this.getClickData("left", 3)},
          {label: "Right Click", fill: false, backgroundColor: "#99006600", borderColor: "#006600", borderWidth: 1, data: this.getClickData("right", 3)},
          {
            label: this.fourthLabel,
            fill: false,
            backgroundColor: "#99000000",
            borderColor: "#00468b",
            borderWidth: 1,
            data: this.getClickData("fourth", this.fourthMultiplier)
          }
        ]
      }
    });
  };

  getChannelData = (val) => {
    var ar = [];
    if (val == 1) {
      for (var i = 0; i < this.ch1Array.length; i++) {
        ar.push(this.ch1Array[i]);
      }
    } else if (val == 2) {
      for (var i = 0; i < this.ch2Array.length; i++) {
        ar.push(this.ch2Array[i]);
      }
    } else if (val == 3) {
      for (var i = 0; i < this.ch3Array.length; i++) {
        ar.push(this.ch3Array[i]);
      }
    } else if (val == 4) {
      for (var i = 0; i < this.ch4Array.length; i++) {
        ar.push(this.ch4Array[i]);
      }
    }
    return ar;
  };

  getClickData = (val, amplitudeMultiplier) => {
    var ar6 = [];
    if (val == "right") {
      for (var i = 0; i < this.rCArray.length; i++) {
        ar6.push(this.rCArray[i] * amplitudeMultiplier);
      }
    } else if (val == "left") {
      for (var i = 0; i < this.lCArray.length; i++) {
        ar6.push(this.lCArray[i] * amplitudeMultiplier);
      }
    } else if (val == "fourth") {
      if (this.parentComponentName == "real_time_game_play") {
        for (var i = 0; i < this.tCArray.length; i++) {
          ar6.push(this.iCArray[i] * amplitudeMultiplier);
        }
      } else {
        for (var i = 0; i < this.tCArray.length; i++) {
          ar6.push(this.tCArray[i] * amplitudeMultiplier);
        }
      }
    }
    return ar6;
  };

  render() {
    return (
      <div style={{width: "100%"}}>
        {this.parentComponentName == "caliberation" ? (
          <div style={{display: "flex", flexDirection: "column", justifyContent: "start", height: "100%"}}>
            <div style={{display: "flex", justifyContent: "flex-start", flexDirection: "column"}}>
              <div style={{display: "flex", justifyContent: "flex-start", flexDirection: "row"}}>
                <div style={{flex: 1}}>
                  <Line data={this.state.first_plot_data} options={this.state.plot_options} height={100} />
                </div>
                <div style={{flex: 1}}>
                  <Line data={this.state.second_plot_data} options={this.state.plot_options} height={100} />
                </div>
              </div>

              <div style={{display: "flex", justifyContent: "flex-start", flexDirection: "row"}}>
                <div style={{flex: 1}}>
                  <Line data={this.state.third_plot_data} options={this.state.plot_options} height={100} />
                </div>
                <div style={{flex: 1}}>
                  <Line data={this.state.fourth_plot_data} options={this.state.plot_options} height={100} />
                </div>
              </div>
            </div>
          </div>
        ) : (
          <div style={{display: "flex", textAlign: "center", width: "100%"}}>
            <div style={{display: "flex", justifyContent: "flex-start", flexDirection: "column", width: "100%"}}>
              <div style={{flex: 1}}>
                <Line data={this.state.first_plot_data} options={this.state.plot_options} height={100} />
              </div>
              <div style={{flex: 1}}>
                <Line data={this.state.second_plot_data} options={this.state.plot_options} height={100} />
              </div>
              <div style={{flex: 1}}>
                <Line data={this.state.third_plot_data} options={this.state.plot_options} height={100} />
              </div>
              <div style={{flex: 1}}>
                <Line data={this.state.fourth_plot_data} options={this.state.plot_options} height={100} />
              </div>
            </div>
          </div>
        )}
      </div>
    );
  }
}
const styles = (theme) => ({
  margin: {
    margin: theme.spacing.unit
  },
  extendedIcon: {
    marginRight: theme.spacing.unit
  }
});

export default withStyles(styles, {withTheme: true})(SignalsComp);