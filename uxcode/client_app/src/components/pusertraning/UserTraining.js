import React, { Component } from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import { Line } from 'rc-progress';
import { Bar } from 'react-chartjs-2';


class UserTraining extends Component {

  constructor(props) {
    super(props)
    this.state = {
    }
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
          padding: '10%',
        }}>

          <div style={{ display: 'flex', justifyContent: 'center', paddingBottom: 20 }}>
            <h5>User Training</h5>
          </div>

          <div style={{ display: 'flex', justifyContent: 'flex-start' }}>
            <div style={{ flex: 1 }}>
              <p>Relax</p>
            </div>
            <div style={{ flex: 4 }}>
              <Line percent="35" strokeWidth="4" strokeColor="#55A747" />
            </div>
            <div style={{ flex: 1, paddingLeft: 20 }}>
              <p>35%</p>
            </div>
          </div>

          <div style={{ display: 'flex', justifyContent: 'flex-start' }}>
            <div style={{ flex: 1 }}>
              <p>Delay</p>
            </div>
            <div style={{ flex: 4 }}>
              <Line percent="55" strokeWidth="4" strokeColor="#F8C133" />
            </div>
            <div style={{ flex: 1, paddingLeft: 20 }}>
              <p>55 ms</p>
            </div>
          </div>


          <div style={{ display: 'flex', justifyContent: 'center'}}>
            <Bar
              data={data}
              options={{
                maintainAspectRatio: true
              }}
            />
          </div>
        </div>
      </div>
    )
  }
}

const styles = theme => ({
  root: {
    height: '100%',
    width: '100%',
    padding: '10%',
    backgroundColor: 'red',
  },
});


const data = {
  labels: ['True Positives', 'False Positves'],
  datasets: [
    {
      label: 'Click Analysis',
      backgroundColor: 'rgba(255,99,132,0.2)',
      borderColor: 'rgba(255,99,132,1)',
      borderWidth: 1,
      hoverBackgroundColor: 'rgba(255,99,132,0.4)',
      hoverBorderColor: 'rgba(255,99,132,1)',
      data: [90, 5]
    }
  ]
};


export default withStyles(styles, { withTheme: true })(UserTraining);