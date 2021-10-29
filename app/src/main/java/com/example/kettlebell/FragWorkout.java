package com.example.kettlebell;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.navigation.NavigationView;

import org.w3c.dom.Text;

public class FragWorkout extends Fragment{
    private EditText numSets;
    private EditText numReps;
    private EditText numWeight;
    private Spinner exercise;
    private TextView result;
    private Button startWorkout;
    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.frag_workout, container, false);
        exercise = view.findViewById(R.id.exerciseSelect);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this.getActivity(),R.array.exercises, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        exercise.setAdapter(adapter);
        numSets = view.findViewById(R.id.numSets);
        numReps = view.findViewById(R.id.numReps);
        numWeight = view.findViewById(R.id.weight);
        startWorkout = view.findViewById(R.id.startWorkout);
        result = view.findViewById(R.id.result);

        startWorkout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String sets = numSets.getText().toString();
                String reps = numReps.getText().toString();
                String weight = numWeight.getText().toString();
                String chosenExercise = exercise.getSelectedItem().toString();
                String input = "The user wants to do "+chosenExercise+" for "+sets+" sets of "+reps+" reps using a weight of "+weight+" lbs.";
                result.setText(input);
            }
        });
        return view;
    }

}
