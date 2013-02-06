// This is brl/bseg/boxm2/volm/boxm2_volm_matcher_p1.h
#ifndef boxm2_volm_matcher_p1_h_
#define boxm2_volm_matcher_p1_h_
//:
// \file
// \brief  A class to match a voxelized query volume to an indexed reference volume based on the depth value and relative order of voxels.
// The index and hypotheses are now referred by \a volm_geo_index.
//
// \author Yi Dong
// \date January 21, 2012
// \verbatim
//   Modifications
// \endverbatim
//

#include <volm/volm_query_sptr.h>
#include <volm/volm_query.h>
#include <volm/volm_io.h>
#include <volm/volm_geo_index_sptr.h>
#include <volm/volm_geo_index.h>
#include <volm/volm_loc_hyp.h>
#include <volm/volm_loc_hyp_sptr.h>
#include "boxm2_volm_wr3db_index_sptr.h"
#include "boxm2_volm_wr3db_index.h"
#include <bocl/bocl_manager.h>
#include <bocl/bocl_device.h>
#include <bocl/bocl_kernel.h>
#include <bocl/bocl_mem.h>

class boxm2_volm_score_out;

class boxm2_volm_matcher_p1
{
 public:
  //: default constructor
  boxm2_volm_matcher_p1() {}
  //: constructor
  boxm2_volm_matcher_p1(volm_query_sptr const& query,
                        vcl_vector<volm_geo_index_node_sptr> const& leaves,
                        float const& buffer_capacity,
                        vcl_string const& geo_index_folder,
                        unsigned const& tile_id,
                        vcl_vector<float> const& depth_interval,
                        vgl_polygon<double> const& cand_poly,
                        bocl_device_sptr gpu,
                        bool const& is_candidate,
                        bool const& is_last_pass,
                        vcl_string const& out_folder,
                        float const& threshold,
                        unsigned const& max_cam_per_loc,
                        bool const& use_orient = false);

  //: destructor
  ~boxm2_volm_matcher_p1();
  //: matcher function
  bool volm_matcher_p1();
  //: generate output -- probability map, binary score file, etc
  bool write_matcher_result(vcl_string const& tile_fname_bin, vcl_string const& tile_fname_txt);
  bool write_matcher_result(vcl_string const& tile_fname_bin);
  //: for testing purpose -- output score for all camera (should only be used for ground truth location)
  bool write_matcher_result_all(unsigned const& leaf_id, unsigned const& hypo_id, vcl_string const& out_fname);

 private:
  //: query, indices, device
  volm_query_sptr                                   query_;
  vcl_vector<volm_geo_index_node_sptr>             leaves_;
  boxm2_volm_wr3db_index_sptr                         ind_;
  boxm2_volm_wr3db_index_sptr                  ind_orient_;
  float                                        ind_buffer_;
  vcl_stringstream                          file_name_pre_;

  //: option to use orientation attirbute
  bool                                         use_orient_;

  //: shell container size
  unsigned                                     layer_size_;
  unsigned*                               layer_size_buff_;
  bocl_mem*                             layer_size_cl_mem_;
  //: candidate list
  bool                                       is_candidate_;
  vgl_polygon<double>                           cand_poly_;
  //: score profile from last matcher
  bool                                       is_last_pass_;
  vcl_string                                   out_folder_;
  //: depth interval table
  vcl_vector<float>                        depth_interval_;
  //: kernel related
  bocl_device_sptr                                    gpu_;
  vcl_size_t                             local_threads_[2];
  vcl_size_t                            global_threads_[2];
  cl_uint                                        work_dim_;
  cl_command_queue                                  queue_;
  cl_ulong                               query_global_mem_;
  cl_ulong                                query_local_mem_;
  cl_ulong                              device_global_mem_;
  cl_ulong                               device_local_mem_;
  vcl_map<vcl_string, vcl_vector<bocl_kernel*> >  kernels_;

  //: query related
  bool                       is_grd_reg_;
  bool                       is_sky_reg_;
  bool                       is_obj_reg_;
  unsigned*                       n_cam_;
  bocl_mem*                n_cam_cl_mem_;
  unsigned*                       n_obj_;
  bocl_mem*                n_obj_cl_mem_;

  unsigned*                 grd_id_buff_;
  bocl_mem*               grd_id_cl_mem_;
  unsigned char*          grd_dist_buff_;
  bocl_mem*             grd_dist_cl_mem_;
  unsigned*          grd_id_offset_buff_;
  bocl_mem*        grd_id_offset_cl_mem_;
  float*                grd_weight_buff_;
  bocl_mem*           grd_weight_cl_mem_;

  unsigned*                 sky_id_buff_;
  bocl_mem*               sky_id_cl_mem_;
  unsigned*          sky_id_offset_buff_;
  bocl_mem*        sky_id_offset_cl_mem_;
  float*                sky_weight_buff_;
  bocl_mem*           sky_weight_cl_mem_;

  unsigned*                 obj_id_buff_;
  bocl_mem*               obj_id_cl_mem_;
  unsigned*          obj_id_offset_buff_;
  bocl_mem*        obj_id_offset_cl_mem_;

  unsigned char*      obj_min_dist_buff_;
  bocl_mem*         obj_min_dist_cl_mem_;
  unsigned char*         obj_order_buff_;
  bocl_mem*            obj_order_cl_mem_;
  float*                obj_weight_buff_;
  bocl_mem*           obj_weight_cl_mem_;
  unsigned char*        obj_orient_buff_;
  bocl_mem*           obj_orient_cl_mem_;

  //: depth interval
  float*            depth_interval_buff_;
  bocl_mem*       depth_interval_cl_mem_;
  unsigned*           depth_length_buff_;
  bocl_mem*         depth_length_cl_mem_;

  //: indices related
  unsigned*                       n_ind_;

  //: output related
  // threshold that only the camera with score higher than threshold will be considered to put into output
  float                            threshold_;
  // maximum number of cameras for each location
  unsigned                   max_cam_per_loc_;
  vcl_vector<volm_score_sptr>      score_all_;


  //: transfer volm_query to 1D array for kernel calculation
  bool transfer_query();
  //: transfer volm_query orientation information to 1D array for kernel calculation, if necessary
  bool transfer_orient();
  //: read given number of indeices from volo_geo_index
  bool fill_index(unsigned const& n_ind,
                  unsigned const& layer_size,
                  unsigned& leaf_id,
                  unsigned char* index_buff,
                  vcl_vector<unsigned>& l_id,
                  vcl_vector<unsigned>& h_id,
                  unsigned& actual_n_ind);
  //: read given number of indeice from volm_geo_index, with two index files, index depth and index orientation
  bool fill_index_orient(unsigned const& n_ind,
                         unsigned const& layer_size,
                         unsigned& leaf_id,
                         unsigned char* index_buff,
                         unsigned char* index_orient_buff,
                         vcl_vector<unsigned>& l_id,
                         vcl_vector<unsigned>& h_id,
                         unsigned& actual_n_ind);
  //: check the given leaf has un-read hypothesis or not
  bool is_leaf_finish(unsigned const& leaf_id);
  //: clare all query cl_mem pointer
  bool clean_query_cl_mem();
  //: compile kernel
  bool compile_kernel(vcl_vector<bocl_kernel*>& vec_kernels);
  //: create queue
  bool create_queue();
   //: kernel execution function
  bool execute_matcher_kernel(bocl_device_sptr                         device,
                              cl_command_queue&                         queue,
                              vcl_vector<bocl_kernel*>                   kern,
                              bocl_mem*                         n_ind_cl_mem_,
                              bocl_mem*                         index_cl_mem_,
                              bocl_mem*                         score_cl_mem_,
                              bocl_mem*                            mu_cl_mem_);
  // kernel execution function with orientation
  bool execute_matcher_kernel_orient(bocl_device_sptr                  device,
                                     cl_command_queue&                  queue,
                                     vcl_vector<bocl_kernel*>        kern_vec,
                                     bocl_mem*                  n_ind_cl_mem_,
                                     bocl_mem*                  index_cl_mem_,
                                     bocl_mem*           index_orient_cl_mem_,
                                     bocl_mem*                  score_cl_mem_,
                                     bocl_mem*                     mu_cl_mem_);


  //: a test function to check the kernel implementation
  bool volm_matcher_p1_test(unsigned n_ind, unsigned char* index, float* score_buff, float* mu_buff);
  bool volm_matcher_p1_test_ori(unsigned n_ind, unsigned char* index, unsigned char* index_orient, float* score_buff, float* mu_buff);
};

#endif // boxm2_volm_matcher_p1_h_