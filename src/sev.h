//
// SEV supported macro's
//

#ifndef __AMD_SEV_H
#define __AMD_SEV_H

int has_sev;

void sev_detect(void);

#define sev_enabled()   (has_sev)

#endif
