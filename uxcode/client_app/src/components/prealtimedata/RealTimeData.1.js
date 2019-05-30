import React, { Component } from 'react';
import PropTypes from 'prop-types';
import RTChart from 'react-rt-chart';


export default class RealTimeData extends Component {


  constructor(props) {
    super(props)
   
    this.chV1 = 0.0;
    this.chV2 = 0.0;
    this.chV3 = 0.0;
    this.chV4 = 0.0;
    this.left_click = 0;
    this.right_click = 0;
    this.start_time = null;
    
    this.clicksInfoArray = []
    this.state = {
      start_showing_random_clicks: false,
      showCaliberationButton: true,
      openFinishDialog: false
    };
  };


  componentDidMount = () => {
    console.log("Component mounted");
    // setInterval(() => this.forceUpdate(), 1);
    window.startSocket(this.socketData);
    this.start_time =  new Date().getTime();
  }

  socketData = (val) => {
    var jsonObject = JSON.parse(String(val));
    if (jsonObject.type == "real_time_data"){
        this.chV1 = jsonObject.ch_v1;
        this.chV2 = jsonObject.ch_v2;
        this.chV3 = jsonObject.ch_v3;
        this.chV4 = jsonObject.ch_v4;
        this.left_click = jsonObject.left_click;
        this.right_click = jsonObject.right_click;
        if(this.left_click==1){
          console.log("Left Click");
        }
        this.forceUpdate();
    }
    // console.log('\nReceived: ' + String(val) + ' at ' + new Date().getTime());
  }

  getChannel1Data = () =>{
    return this.chV1;
  }

  getChannel2Data = () =>{
    return this.chV2;
  }

  getChannel3Data = () =>{
    return this.chV3;
  }

  getChannel4Data = () =>{
    return this.chV4;
  }

  getLeftClickData = () =>{
    return this.left_click*4;
  }

  getRightClickData = () =>{
    return this.right_click*4;
  }

  getCurrentTime = () =>{
    var val = new Date().getTime() - this.start_time;
    return parseInt(val);
  }


  render() {

    var data = {
      date: this.getCurrentTime(),
      Channel_1: this.getChannel1Data(),
      Channel_2: this.getChannel2Data(),
      Channel_3: this.getChannel3Data(),
      Channel_4: this.getChannel4Data(),
      Left_Click: this.getLeftClickData(),
      Right_Click: this.getRightClickData(),

    };
    var flow = {
      duration: 200
    };

    return (
      <div style={{ height: '100%', width: '100%' }}>
        <div style={{
          display: 'flex',
          flexDirection: 'column',
          justifyContent: 'center',
          height: '100%',
          padding: '5%',
        }}>
          <p>Real Time Data Section</p>


          <div style={{ display: 'flex', justifyContent: 'flex-start' }}>
            <div style={{ flex: 1 }}>
              <RTChart
                // flow={flow}
                maxValues={100}
                fields={['Channel_1', 'Channel_2', 'Channel_3', 'Channel_4', 'Left_Click', 'Right_Click']}
                data={data} />
            </div>
          </div>


        </div>
      </div>
    )
  }
}
