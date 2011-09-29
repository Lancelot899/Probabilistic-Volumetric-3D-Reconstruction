from boxm2_register import boxm2_batch, dbvalue; 

###################################################
# Vil loading and saving
###################################################
def load_image(file_path) : 
  boxm2_batch.init_process("vilLoadImageViewProcess");
  boxm2_batch.set_input_string(0, file_path);
  boxm2_batch.run_process();
  (id,type) = boxm2_batch.commit_output(0);
  (ni_id, ni_type) = boxm2_batch.commit_output(1); 
  (nj_id, nj_type) = boxm2_batch.commit_output(2); 
  ni = boxm2_batch.get_output_unsigned(ni_id); 
  nj = boxm2_batch.get_output_unsigned(nj_id); 
  img = dbvalue(id,type);
  return img, ni, nj; 
  
def save_image(img, file_path) : 
  boxm2_batch.init_process("vilSaveImageViewProcess");
  boxm2_batch.set_input_from_db(0,img);
  boxm2_batch.set_input_string(1,file_path);
  boxm2_batch.run_process();

def convert_image(img, type="byte") :
  boxm2_batch.init_process("vilConvertPixelTypeProcess");
  boxm2_batch.set_input_from_db(0, img);
  boxm2_batch.set_input_string(1, type); 
  boxm2_batch.run_process();
  (id,type) = boxm2_batch.commit_output(0);
  cimg = dbvalue(id,type); 
  return cimg; 

#pixel wise roc process for change detection images
def pixel_wise_roc(cd_img, gt_img, mask_img=None) :
  boxm2_batch.init_process("vilPixelwiseRocProcess");
  boxm2_batch.set_input_from_db(0,cd_img);
  boxm2_batch.set_input_from_db(1,gt_img);
  if mask_img: 
    boxm2_batch.set_input_from_db(2,mask_img); 
  boxm2_batch.run_process();
  (id,type) = boxm2_batch.commit_output(0);
  tp = boxm2_batch.get_bbas_1d_array_float(id);
  (id,type) = boxm2_batch.commit_output(1);
  tn = boxm2_batch.get_bbas_1d_array_float(id);
  (id,type) = boxm2_batch.commit_output(2);
  fp = boxm2_batch.get_bbas_1d_array_float(id);
  (id,type) = boxm2_batch.commit_output(3);
  fn = boxm2_batch.get_bbas_1d_array_float(id);	
  
  #return tuple of true positives, true negatives, false positives, etc..
  return (tp, tn, fp, fn); 
  