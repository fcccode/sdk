#ifndef _ice_checklist_h_
#define _ice_checklist_h_

#include "ice-agent.h"
#include "ice-internal.h"

struct ice_checklist_t;
struct ice_checklist_handler_t
{
	int (*onrolechanged)(void* param);
	int (*onvalid)(void* param, struct ice_checklist_t* l, const ice_candidate_pairs_t* pair);
	int (*onfinish)(void* param, struct ice_checklist_t* l);
};

struct ice_checklist_t* ice_checklist_create(struct ice_agent_t* ice, struct ice_checklist_handler_t* handler, void* param);
int ice_checklist_destroy(struct ice_checklist_t** l);

int ice_checklist_reset(struct ice_checklist_t* l, const ice_candidates_t* locals, const ice_candidates_t* remotes);

int ice_checklist_start(struct ice_checklist_t* l);

int ice_checklist_cancel(struct ice_checklist_t* l);

int ice_checklist_conclude(struct ice_checklist_t* l);

/// on stream valid
int ice_checklist_update(struct ice_checklist_t* l, const ice_candidate_pairs_t* valids);

/// on receive peer connection request
int ice_checklist_trigger(struct ice_checklist_t* l, const struct stun_address_t* addr, int nominated);

/// on role changed
int ice_checklist_onrolechanged(struct ice_checklist_t* l, int controlling);

/// @return 1-running, 0-frozen/completed
int ice_checklist_getstatus(struct ice_checklist_t* l);

#endif /* !_ice_checklist_h_ */