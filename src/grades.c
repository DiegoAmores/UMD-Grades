/*
  Diego Amores
  ID:117010282
*/

#include <stdio.h>
#include <math.h>

/* Prototypes */
int valid_weights(int [], int, int);
void rearrange_array_ascending_order(int [], int [], int [], int [], int);
int whether_to_generate_statistical_info(char);
void compute_math_values(int [], int [], int [], int [], int, int, int, int, char);

/***************************************************************************/
/* The Program reads in points to be deducted, number of assignment drops, */
/* and whether or not if they want statistical information. User will then */
/* put in grades according to assignment number, test score, weight, and   */
/* days late. It will then prompt the numeric score and whether or not     */
/* theyu chose to view statistical information.                            */
/***************************************************************************/
int main(){
  int points_penalty_per_day, number_of_drop_assignments, number_of_assignments, assignment,
  score, weight, days_late, i = 0, number_of_assignments_temp;
  
  int assignment_arr[50], score_arr[50], weight_arr[50], days_late_arr[50];
  char generate_statistical_info;

  /* read values */
  scanf("%d%d %c", &points_penalty_per_day, &number_of_drop_assignments, &generate_statistical_info);
  scanf("%d", &number_of_assignments);
  
  number_of_assignments_temp = number_of_assignments;

  do{
    /* reading assignment, score, weight,and days late */
    scanf("%d%*c%d%*c%d%*c%d", &assignment, &score, &weight, &days_late);
    
    assignment_arr[i] = assignment;
    score_arr[i] = score;
    weight_arr[i] = weight;
    days_late_arr[i] = days_late;
    
    i++;
    number_of_assignments_temp--;
  } while(number_of_assignments_temp != 0);
  
  if(valid_weights(weight_arr, number_of_drop_assignments, i) > 0){
    rearrange_array_ascending_order(assignment_arr, score_arr, weight_arr, days_late_arr, i);
    compute_math_values(assignment_arr, score_arr, weight_arr, days_late_arr,
    number_of_assignments, points_penalty_per_day, number_of_drop_assignments, i, generate_statistical_info);
  }
  else{
    printf("ERROR: Invalid values provided");
    return 0;
  }
     
  return 0;
}

/*********************************************************/
/* Determines whether or not all combined weights        */
/* are equal to 100 and returns true and if they're were */
/* dropped asignments it returns true, otherwise         */
/* return false                                          */
/*********************************************************/
int valid_weights(int weight[], int number_of_drop_assignments, int size){
  int sum = 0;
  int i;
  
  for(i = 0; i < size; i++)
    sum += weight[i];
  
  if(number_of_drop_assignments > 0)
    return 1;
  
  else if(sum != 100){
    return 0;
  }
  
  else
    return 1;
}

/*********************************************/
/* This function takes in 5 parameters       */
/* in which we store assignment numbers,     */
/* scores, weights,and days late into        */
/* different arrays and swaps them according */
/* assignment number                         */
/*********************************************/
void rearrange_array_ascending_order(int assignment_arr[], int score_arr[], int weight_arr[], int days_late_arr[], int size){
  int i, j;
  int temp_assignment, temp_score, temp_weight, temp_days_late;

  for(i = 0; i < size; i++){
    
    for(j = 0; j < size; j++){
      if(assignment_arr[i] < assignment_arr[j]){
		  temp_assignment = assignment_arr[i];
		  assignment_arr[i] = assignment_arr[j];
		  assignment_arr[j] = temp_assignment;
		  
		  temp_score = score_arr[i];
		  score_arr[i] = score_arr[j];
		  score_arr[j] = temp_score;
		  
		  temp_weight = weight_arr[i];
		  weight_arr[i] = weight_arr[j];
		  weight_arr[j] = temp_weight;
		  
		  temp_days_late = days_late_arr[i];
		  days_late_arr[i] = days_late_arr[j];
		  days_late_arr[j] = temp_days_late;
	
      }
    }
  }
}

/***************************************/
/* Whether or not the user typed 'Y'   */
/* || 'y' return 1, otherwise return 0 */
/***************************************/
int whether_to_generate_statistical_info(char generate_statistical_info){
  if(generate_statistical_info == 'Y' || generate_statistical_info == 'y')
    return 1;
  else
    return 0;
}

/**************************************************************/
/* Compute the math values for numeric score given the sorted */
/* arrays based on whether or not assignments were dropped    */
/* and whether or not user wanted statistical information     */
/**************************************************************/
void compute_math_values(int assignment_arr[], int score_arr[], int weight_arr[], int days_late_arr[], int number_of_assignments, int points_penalty_per_day, int number_of_drop_assignments, int size, char generate_statistical_info){
  double numeric_score = 0.0, mean = 0.0, standard_deviation = 0.0, sum = 0.0;
  int i, j, k;

  /*if score minus the late penalty is less than 0 add 0 if not add values*/
  for(i = 0; i < size; i++){
    if(score_arr[i] - (points_penalty_per_day * days_late_arr[i]) < 0)
      sum += 0;
    else
      sum += score_arr[i] - (points_penalty_per_day * days_late_arr[i]);
  }

  /*calculare mean*/
  mean = sum / number_of_assignments;

  for(i = 0; i < size; i++){
    if(score_arr[i] - (points_penalty_per_day * days_late_arr[i]) < 0)
      standard_deviation += pow(0 - mean, 2);
    else
      standard_deviation += pow((score_arr[i] - (points_penalty_per_day * days_late_arr[i])) - mean, 2);
  }

  standard_deviation = sqrt(standard_deviation /  number_of_assignments);
  
  for(i = 0; i < size; i++){
	  if(score_arr[i] - (points_penalty_per_day * days_late_arr[i]) < 0)
		  numeric_score += 0;
	  else if(score_arr[i] - (points_penalty_per_day * days_late_arr[i]) >= 0)
		  numeric_score += (score_arr[i] - (points_penalty_per_day * days_late_arr[i])) * weight_arr[i] / 100.0;
  }
  
  if(number_of_drop_assignments == 0 && whether_to_generate_statistical_info(generate_statistical_info) == 1){
    printf("Numeric Score: %5.4f\n", numeric_score);
    printf("Points Penalty Per Day Late: %d\n", points_penalty_per_day);
    printf("Number of Assignments Dropped: %d\n", number_of_drop_assignments);
    printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");

    for(i = 0; i < size; i++)
      printf("%d, %d, %d, %d\n", assignment_arr[i], score_arr[i], weight_arr[i], days_late_arr[i]);

    printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, standard_deviation);
	
  } else if(number_of_drop_assignments == 0 && whether_to_generate_statistical_info(generate_statistical_info) == 0){
	  printf("Numeric Score: %5.4f\n", numeric_score);
	  printf("Points Penalty Per Day Late: %d\n", points_penalty_per_day);
	  printf("Number of Assignments Dropped: %d\n", number_of_drop_assignments);
	  printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");
	  
	  for(i = 0; i < size; i++)
		  printf("%d, %d, %d, %d\n", assignment_arr[i], score_arr[i], weight_arr[i], days_late_arr[i]);
  
  } else if(number_of_drop_assignments <= number_of_assignments - 1 && number_of_drop_assignments > 0){
	  double lowest = 101.0, sum_scores = 0.0, sum_weight = 0.0;
	  double lowest_scores [50];
	  
	  for(i = 0; i < number_of_assignments; i++){
		  lowest_scores[i] = (score_arr[i]  * (weight_arr[i] / 100.0));
	  }
	  
	  for(i = 0; i < number_of_drop_assignments; i++){
		  for(j = 0; j < number_of_assignments; j++){
			  if(lowest_scores[j] < lowest && lowest_scores[j] != -1)
				  lowest = lowest_scores[j];
		  }
		  
		  for(k = 0; k < number_of_assignments; k++){
			  if(lowest_scores[k] == lowest){
				  lowest_scores[k] = -1;
				  lowest = 101;
			  }
		  }
	  }
	  
	  for(i = 0; i < size; i++){
		  if(lowest_scores[i] != -1)
			  if(score_arr[i] - (points_penalty_per_day * days_late_arr[i]) < 0)
				  lowest_scores[i] = 0;
			  else 
				  lowest_scores[i] = (score_arr[i]-(points_penalty_per_day*days_late_arr[i]))*weight_arr[i]/100.0;
	  }
  }
  
  for(j = 0; j < number_of_assignments; j++){
	  if(lowest_scores[j] != -1){
		  sum_scores += lowest_scores[j];
		  sum_weight += weight_arr[j] / 100.0;
	  }
  }
  
  numeric_score = sum_scores / sum_weight;
  
  if(whether_to_generate_statistical_info(generate_statistical_info) == 0){
	  printf("Numeric Score: %5.4f\n", numeric_score);
      printf("Points Penalty Per Day Late: %d\n", points_penalty_per_day);
      printf("Number of Assignments Dropped: %d\n", number_of_drop_assignments);
      printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");

      for(i = 0; i < size; i++)
		  printf("%d, %d, %d, %d\n", assignment_arr[i], score_arr[i], weight_arr[i], days_late_arr[i]);
	  
  } else if(whether_to_generate_statistical_info(generate_statistical_info) == 1){
	  printf("Numeric Score: %5.4f\n", numeric_score);
      printf("Points Penalty Per Day Late: %d\n", points_penalty_per_day);
      printf("Number of Assignments Dropped: %d\n", number_of_drop_assignments);
      printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");
	  
	  for(i = 0; i < size; i++)
		  printf("%d, %d, %d, %d\n", assignment_arr[i], score_arr[i], weight_arr[i], days_late_arr[i]);
	  printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, standard_deviation);
  }
}

