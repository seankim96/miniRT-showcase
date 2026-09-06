/* Cornell Box input replay: all scene edits go through the unchanged user
 * keyboard/mouse callbacks. No direct transform, camera or selection writes. */
#include "raytracing.h"
#include "camera.h"
#include "wrapper.h"
#include "hittable_list.h"
#include <string.h>

static void key(t_vars *v, int code, int frame)
{
 t_wrapper *objects[256]; t_transform_info before[256];
 t_hittable_list *lists[3]={v->objs_list,v->planes_list,v->lights};
 t_camera cam=*v->camera;
 int n=0, changed=0;
 for(int l=0;l<3;l++) for(int i=0;i<lists[l]->size;i++) {
  if(n>=256) {fprintf(stderr,"Too many objects for replay verification\n");exit(3);}
  objects[n]=(t_wrapper *)lists[l]->hittables[i];
  before[n]=objects[n]->trans_info;n++;
 }
 key_hooks(code,v);
 for(int i=0;i<n;i++) if(memcmp(&before[i],&objects[i]->trans_info,sizeof(before[i]))) changed++;
 int camera_changed=memcmp(&cam,v->camera,sizeof(cam))!=0;
 if(changed+camera_changed>1) {fprintf(stderr,"FAIL: multiple targets changed at frame %d\n",frame);exit(3);}
 fprintf(stderr,"frame=%d key=%d changed_objects=%d changed_camera=%d\n",frame,code,changed,camera_changed);
 if(v->m_flag=='1'&&v->f_flag==E) fprintf(stderr,"FOV=%.0f\n",v->camera->fov);
 if(v->m_flag=='3'&&v->f_flag==E) {
  t_wrapper *selected=(t_wrapper *)v->curr_obj;
  fprintf(stderr,"size radius=%.2f length=%.2f\n",selected->trans_info.scale.x,selected->trans_info.scale.y);
  if(selected->trans_info.scale.x<=0||selected->trans_info.scale.y<=0||selected->trans_info.scale.z<=0) {
   fprintf(stderr,"FAIL: nonpositive object dimensions\n");exit(3);
  }
 }
}

static void replay(t_vars *v,int f)
{
 if(f==10) key(v,'1',f);
 if(f==11) key(v,E,f);
 if(f>=12&&f<=84&&(f-12)%3==0) key(v,MINUS,f);
 if(f==120) {
  /* Earth center projected at x=437,y=225 with FOV=65. Normal mouse picking. */
  mouse_hooks(1,437,225,v);
  t_wrapper *picked=(t_wrapper *)v->curr_obj;
  if(v->is_plane||fabs(picked->trans_info.pos.x+3)>1e-8||fabs(picked->trans_info.pos.z-8)>1e-8) {
   fprintf(stderr,"FAIL: mouse did not select Earth\n");exit(3);
  }
  fprintf(stderr,"frame=120 left_click=(437,225) selected=Earth\n");
 }
 if(f==122) key(v,'3',f);
 if(f==124) key(v,W,f);
 if(f>=132&&f<=162&&(f-132)%10==0) key(v,SIX,f);
 if(f>=182&&f<=212&&(f-182)%10==0) key(v,FOUR,f);
 if(f==240) key(v,'3',f);
 if(f==241) key(v,Q,f);
 if(f>=250&&f<=342&&(f-250)%4==0) key(v,(f-250)/4<12?EIGHT:TWO,f);
 if(f==360) key(v,'2',f);
 if(f==361) key(v,W,f);
 if(f>=374&&f<=449&&(f-374)%5==0) key(v,(f-374)/5<8?SIX:FOUR,f);
 if(f==480) key(v,'1',f);
 if(f==481) key(v,Q,f);
 if(f>=494&&f<=582&&(f-494)%8==0) {
  int step=(f-494)/8;
  key(v,step<3||step>=9?FOUR:SIX,f);
 }
 if(f==600) {
  mouse_hooks(1,605,225,v);
  t_wrapper *picked=(t_wrapper *)v->curr_obj;
  if(v->is_plane||fabs(picked->trans_info.pos.x-3)>1e-8||fabs(picked->trans_info.pos.z-10)>1e-8) {
   fprintf(stderr,"FAIL: mouse did not select hyperboloid\n");exit(3);
  }
  fprintf(stderr,"frame=600 left_click=(605,225) selected=hyperboloid\n");
 }
 if(f==602) key(v,'3',f);
 if(f==604) key(v,Q,f);
 /* Tilt the selected shape by 45 degrees using nine ordinary key presses,
  * so length changes are visible from this camera. */
 if(f>=610&&f<=642&&(f-610)%4==0) key(v,SIX,f);
 if(f==646) key(v,E,f);
 if(f==655||f==670) key(v,SIX,f);
 if(f==685||f==700) key(v,FOUR,f);
 if(f==720||f==840) {
  t_wrapper *selected=(t_wrapper *)v->curr_obj;
  if(fabs(selected->trans_info.scale.x-0.5)>1e-8||fabs(selected->trans_info.scale.y-3)>1e-8) {
   fprintf(stderr,"FAIL: dimensions did not return to original\n");exit(3);
  }
  fprintf(stderr,"PASS: original radius and length restored at frame %d\n",f);
 }
 if(f==722) key(v,'3',f);
 if(f==724) key(v,E,f);
 if(f==732||f==747||f==762) key(v,EIGHT,f);
 if(f==777||f==792||f==807) key(v,TWO,f);
 if(f==842) key(v,'1',f);
 if(f==844) key(v,E,f);
 if(f>=848&&f<=896&&(f-848)%2==0) key(v,PLUS,f);
 if(f>=906&&f<=954&&(f-906)%2==0) key(v,MINUS,f);
 if(f==959&&fabs(v->camera->fov-65)>1e-8) {
  fprintf(stderr,"FAIL: FOV did not return to 65\n");exit(3);
 }
}

int main(int argc,char **argv)
{
 t_vars v={0};t_data data={0};t_camera camera={0};
 static unsigned char rgb[X_MAX*Y_MAX*3];
 int frames=argc>2?atoi(argv[2]):960;
 if(argc<2) return 1;
 v.data=&data;v.camera=&camera;
 if(initialize(&v,argv[1])<0) return 1;
 for(int f=0;f<frames;f++) {
  replay(&v,f);
  if(v.dirty_c||v.dirty_l||v.dirty_o) {
   render(&v);mlx_do_sync(v.mlx);
   v.dirty_c=false;v.dirty_o=false;
  }
  for(int y=0;y<Y_MAX;y++) for(int x=0;x<X_MAX;x++) {
   unsigned int p=*(unsigned int *)(data.addr+y*data.line_length+x*(data.bits_per_pixel/8));
   int n=(y*X_MAX+x)*3;rgb[n]=(p>>16)&255;rgb[n+1]=(p>>8)&255;rgb[n+2]=p&255;
  }
  if(fwrite(rgb,1,sizeof(rgb),stdout)!=sizeof(rgb)) return 2;
 }
 fflush(stdout);
 fprintf(stderr,"PASS: all inputs changed at most one target; no direct scene edits.\n");
 return destroy_exit(&v);
}
