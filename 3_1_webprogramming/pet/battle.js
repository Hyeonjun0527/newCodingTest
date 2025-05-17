const socket = new WebSocket("wss://api.example.com/battle");
const joinBtn  = document.getElementById("join-queue");
const leaveBtn = document.getElementById("leave-queue");
const statusEl = document.getElementById("status");
const teamsBox = document.getElementById("teams");
const teamAEl  = document.getElementById("teamA");
const teamBEl  = document.getElementById("teamB");

joinBtn.onclick = () => {
  socket.send(JSON.stringify({type:"join_queue"}));
  joinBtn.hidden  = true;
  leaveBtn.hidden = false;
  statusEl.textContent = "대기열에 참가했습니다. 매칭 중…";
};

leaveBtn.onclick = () => {
  socket.send(JSON.stringify({type:"leave_queue"}));
  resetUI();
};

socket.onmessage = (ev) => {
  const msg = JSON.parse(ev.data);

  if (msg.type === "match_found") {
    // msg = { room_id, teamA:[{nick}], teamB:[{nick}] }
    renderTeams(msg.teamA, msg.teamB);
  }
};

function renderTeams(a, b){
  teamAEl.innerHTML = a.map(p=>`<li>${p.nick}</li>`).join("");
  teamBEl.innerHTML = b.map(p=>`<li>${p.nick}</li>`).join("");
  teamsBox.hidden   = false;
  statusEl.textContent = "팀 편성이 완료되었습니다!";
  leaveBtn.hidden = true;
}

function resetUI(){
  joinBtn.hidden = false;
  leaveBtn.hidden = true;
  teamsBox.hidden = true;
  statusEl.textContent = "대기열에 참가하지 않았습니다.";
}
