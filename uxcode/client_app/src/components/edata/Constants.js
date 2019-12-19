export const CURRENT_IMPULSE_STATE = {
  RUNNING_USER_TRAINING: "running_user_training",
  RUNNING_REAL_TIME: "running_real_time",
  SCREEN_WELCOME: "screen_welcome",
  SCREEN_CALIBERATION: "screen_caliberation",
  SCREEN_USER_TRAINING: "screen_user_training",
  SCREEN_REPORT: "screen_report",
  SCREEN_REAL_TIME: "screen_real_time"
};

var currentState;

export function getCurrentState() {
  return currentState;
}

export function setCurrentState(value) {
  currentState = value;
}
