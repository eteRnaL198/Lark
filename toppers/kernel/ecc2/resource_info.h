#ifndef _RESOURCE_INFO_H_
#define _RESOURCE_INFO_H_
#include "added_field.h"
#include "task.h"


#ifndef RESMAP_BIT
#define RESMAP_BIT(resid) (1u<<(resid))
#endif
extern TaskType rescb_usingtask[];	/* リソース使用中タスクID */
extern UINT16 rescb_bitmap[];	/* リソース獲得状況ビットマップ */
extern UINT8 rescb_used;
extern const UINT8 res_arr;

extern const UINT16 tinib_resource[][RES_ARR];

#endif
