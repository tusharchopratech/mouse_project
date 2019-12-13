import React, { Component } from 'react';
import { withStyles } from '@material-ui/core/styles';
import Fab from '@material-ui/core/Fab';
import Button from '@material-ui/core/Button';
import {ReactComponent as WaveIconWhite} from "../../images/wave_white.svg";

class Welcome extends Component {

    constructor(props) {
        super(props)
        this.state = {
            openLoadingDialog: true,
        }
    }

    startCaliberation = () => {
        this.props.callbackSetMainSection('caliberation');
    };

    componentDidMount = () => {
        console.log("Welcome mounted");
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.send("socket_data_send", "stop_raw_real_time_data");
    };

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
                        <p>Welcome to the world of cybernetnics. Please start caliberation. </p>
                    </div>
                    <div style={{ display: 'flex', justifyContent: 'center', paddingBottom: 20 }}>
                        <Fab variant="extended" color="primary" aria-label="Add" onClick={this.startCaliberation} className={classes.margin}>
                            <WaveIconWhite className={classes.extendedIcon} />
                            Start Glove Caliberation
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

export default withStyles(styles, { withTheme: true })(Welcome);