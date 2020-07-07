const btnLed = document.querySelector(".led .btn-on-off");
const btnDoor = document.querySelector(".door .btn-on-off");
const btnEscu = document.querySelector(".escalator .btn-on-off");
const btnUpEsc = document.querySelector(".escalator .toogleDirect .up");
const btnDownEsc = document.querySelector(".escalator .toogleDirect .down");
const slideSpeedEsc = document.querySelector(".escalator .slideSpeed input");
const indexSpeed = document.querySelector(".escalator .slideSpeed p");
slideSpeedEsc.addEventListener("change", (e) => updateSpeed(e));
btnLed.addEventListener("click", (e) => toogleStatus(e));
btnDoor.addEventListener("click", (e) => toogleStatus(e));
btnEscu.addEventListener("click", (e) => toogleStatus(e));
btnUpEsc.addEventListener("click", (e) => toogleDirect(e));
btnDownEsc.addEventListener("click", (e) => toogleDirect(e));
const toogleDirect = (e) => {
  const btn = e.target;
  const status = btn.classList[2];
  if (status !== "notChoose") {
    if (btn.classList[1] == "up") {
      database.ref("/escalator/clockwise").set(0, (err) => {
        if (err) {
          console.log(err);
        } else {
          btn.classList.add("notChoose");
          btnDownEsc.classList.remove("notChoose");
          console.log("updated");
        }
      });
    }
    if (btn.classList[1] == "down") {
      database.ref("/escalator/clockwise").set(1, (err) => {
        if (err) {
          console.log(err);
        } else {
          btn.classList.add("notChoose");
          btnUpEsc.classList.remove("notChoose");
          console.log("updated");
        }
      });
    }
  }
};
const toogleStatus = (e) => {
  const btn = e.target;
  const status = btn.classList[1];
  let type = btn.parentElement.classList[0];
  let ref = "";
  if (type == "led") {
    ref = "/light";
  }
  if (type == "escalator") {
    ref = "/escalator/currentStatus";
  }
  if (type == "door") {
    ref = "/door";
  }
  if (status == "on") {
    database.ref(`${ref}`).set(0, (err) => {
      if (err) {
        console.log(err);
      } else {
        btn.classList.remove("on");
        btn.classList.add("off");
      }
    });
  }
  if (status == "off") {
    database.ref(`${ref}`).set(1, (err) => {
      if (err) {
        console.log(err);
      } else {
        btn.classList.remove("off");
        btn.classList.add("on");
      }
    });
  }
};
const updateSpeed = () => {
  const speedEsc = slideSpeedEsc.value;
  database.ref("/escalator/speed").set(parseInt(speedEsc), (err) => {
    if (err) {
      console.log(err);
    } else {
      indexSpeed.innerHTML = speedEsc;
    }
  });
};
