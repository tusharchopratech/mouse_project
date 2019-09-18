import React, { Component } from 'react';
import { withStyles } from '@material-ui/core/styles';
import Fab from '@material-ui/core/Fab';
import Button from '@material-ui/core/Button';
import Snackbar from '@material-ui/core/Snackbar';
import { ReactComponent as HandIconWhite } from '../../images/hand_white.svg';


class RealTimeData extends Component {

    constructor(props) {
        super(props)
        this.state = {
            openLoadingDialog: true,
            buttonText: 'Start Real Time Play',
            buttonText2: 'Stop Real Time Play',
            openSnackBar: false,
            snackBarText: 'Impulse started succesfully. Please start the game.',
            osLeftClicks: [],
            osRightClicks: [],
            impulseLeftClicks: [],
            impulseRightClicks: [],
        }
    }

    startCaliberation = () => {
        this.props.callbackSetMainSection('caliberation');
    };

    startRealTime = () => {
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.send("socket_data_send", "start_real_time");
    };

    stopRealTime = () => {
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.send("socket_data_send", "stop_real_time");
    };

    componentDidMount = () => {
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.on('socket_data_received', function (event, data) {
            var jsonObject = JSON.parse(String(data));
            if (jsonObject.type == "start_real_time_success") {
                this.setState({ buttonText: 'Stop Real Time Play', snackBarText: 'Impulse started succesfully. Please start the game.', openSnackBar: true });
                setTimeout(function () { this.setState({ openSnackBar: false }); }.bind(this), 4000);
            } else if (jsonObject.type == "real_time_results") {
                this.setState({
                    osLeftClicks: jsonObject.os_left_clicks,
                    osRightClicks: jsonObject.os_right_clicks,
                    impulseLeftClicks: jsonObject.impulse_left_clicks,
                    impulseRightClicks: jsonObject.impulse_right_clicks,
                });
            }
        }.bind(this));
    };

    render() {
        const { classes } = this.props;
        return (
            <div style={{ height: '100%', width: '100%' }}>
                <div style={{
                    display: 'flex',
                    flexDirection: 'column',
                    justifyContent: 'top',
                    height: '100%',
                    padding: '10%',
                }}>
                    <div style={{ display: 'flex', justifyContent: 'center', paddingBottom: 20 }}>
                        <Fab variant="extended" color="primary" aria-label="Add" onClick={this.startRealTime} className={classes.margin}>
                            <HandIconWhite className={classes.extendedIcon} />
                            {this.state.buttonText}
                        </Fab>
                    </div>
                    <div style={{ display: 'flex', justifyContent: 'center', paddingBottom: 20 }}>
                        <Fab variant="extended" color="primary" aria-label="Add" onClick={this.stopRealTime} className={classes.margin}>
                            <HandIconWhite className={classes.extendedIcon} />
                            {this.state.buttonText2}
                        </Fab>
                    </div>
                </div>

                <div>
                    <div>
                        Actual Left Click Timestamps :
                        <pre>{JSON.stringify(this.state.osLeftClicks)}</pre>
                    </div>
                    <div>
                        Actual Right Click Timestamps :
                        <pre>{JSON.stringify(this.state.osRightClicks)}</pre>
                    </div>

                    <div>
                        Impulse Left Click Timestamps :
                        <pre>{JSON.stringify(this.state.impulseLeftClicks)}</pre>
                    </div>
                    <div>
                        Impulse Right Click Timestamps :
                        <pre>{JSON.stringify(this.state.impulseRightClicks)}</pre>
                    </div>

                </div>


                <Snackbar
                    anchorOrigin={{
                        vertical: 'bottom',
                        horizontal: 'left',
                    }}
                    open={this.state.openSnackBar}
                    ContentProps={{
                        'aria-describedby': 'message-id',
                    }}
                    message={<span id="message-id">{this.state.snackBarText}</span>}
                />
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

export default withStyles(styles, { withTheme: true })(RealTimeData);