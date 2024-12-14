#include "../connecter.h"
void abolish_states(states* USA){
  // Make a new temp list
  states* one_state = malloc(STATES*sizeof(states));
  if (!one_state) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  // Define all values in list as 0 or empty, except for stateName[0]
  for(int i = 0; i < STATES; i++) {
    strcpy(one_state[i].stateName, "empty");
    one_state[i].electors = 0;
    one_state[i].democrats = 0.0;
    one_state[i].republicans = 0.0;
    one_state[i].third_party = 0.0;
    one_state[i].population = 0;
    one_state[i].dem_votes = 0;
    one_state[i].rep_votes = 0;
    one_state[i].third_votes = 0;
    if(i==0) {
      strcpy(one_state[i].stateName, "one_state");
    }
  }
  // Insert all USA list data within the temp list on its [0] position
  for(int i=0;i<STATES;i++) {
    one_state->electors += USA[i].electors;
    one_state->democrats += USA[i].democrats;
    one_state->republicans += USA[i].republicans;
    one_state->third_party += USA[i].third_party;
    one_state->population += USA[i].population;
    one_state->dem_votes += USA[i].dem_votes;
    one_state->rep_votes += USA[i].rep_votes;
    one_state->third_votes += USA[i].third_votes;
  }
  // Overwrite the Original USA list with the temp list data
  for(int i=0;i<STATES;i++) {
    strcpy(USA[i].stateName, one_state[i].stateName);
    USA[i].electors = one_state[i].electors;
    USA[i].democrats = one_state[i].democrats;
    USA[i].republicans = one_state[i].republicans;
    USA[i].third_party = one_state[i].third_party;
    USA[i].population = one_state[i].population;
    USA[i].dem_votes = one_state[i].dem_votes;
    USA[i].rep_votes = one_state[i].rep_votes;
    USA[i].third_votes = one_state[i].third_votes;
  }
  free(one_state);
}