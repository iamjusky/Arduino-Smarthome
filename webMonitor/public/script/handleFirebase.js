database.ref("/").once("value", function (data) {
  syncData(data.val());
});
const syncData = ({ door, escalator, light }) => {
  updateStatus(btnDoor, door);
  updateStatus(btnLed, light);
  updateStatus(btnEscu, escalator.currentStatus);
  updateDirectEsc(escalator.clockwise);
  updateSpeedEsc(escalator.speed);
};
const updateSpeedEsc = (data) => {
  slideSpeedEsc.value = data;
  indexSpeed.innerHTML = data;
};
const updateDirectEsc = (data) => {
  if (data == 0) {
    btnDownEsc.classList.remove("notChoose");
    btnUpEsc.classList.add("notChoose");
  }
  if (data == 1) {
    btnUpEsc.classList.remove("notChoose");
    btnDownEsc.classList.add("notChoose");
  }
};
const updateStatus = (btn, data) => {
  if (data == 0) {
    btn.classList.remove("on");
    btn.classList.add("off");
  }
  if (data == 1) {
    btn.classList.remove("off");
    btn.classList.add("on");
  }
};
