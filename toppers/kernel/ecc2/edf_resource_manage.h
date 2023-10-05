#ifndef _EDF_RESOURCE_MANAGE_H_
#define _EDF_RESOURCE_MANAGE_H_

extern TickType rescb_prevdl[];
extern TickType dl_bu;

extern void update_deadline(TaskType);
extern void ref_deadline(TaskType);
extern StatusType GetResource_edf(ResourceType);
extern StatusType ReleaseResource_edf(ResourceType);
extern UINT8 rescb_used;
extern ResourceType rescb_prevres[];

#endif
